/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 13:30:45 by broccoli          #+#    #+#             */
/*   Updated: 2021/05/21 15:57:50 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_sortpush(t_ls_file *head, t_ls_file *node)
{
	t_ls_file *filecur;

	filecur = head;
	while (filecur->next)
	{
		if (!(ls_glob()->options & (1 << 7)) && (filecur == head ||
					ls_comparison(node, filecur)) &&
				ls_comparison(filecur->next, node))
		{
			node->next = filecur->next;
			filecur->next = node;
			return ;
		}
		filecur = filecur->next;
	}
	filecur->next = node;
	node->next = 0;
}

static void	ls_getdata(t_ls_file *files, short *col_width, int i)
{
	files->name_len = ft_strlen(files->basename);
	while (files->name_len >= *col_width * 8)
		(*col_width)++;
	files->name_len > ls_glob()->longest_name ?
		ls_glob()->longest_name = files->name_len : 0;
	ls_glob()->file_count++;
	if (lstat(files->file_name, &files->stat) == -1 &&
			ls_check_error(files->file_name, 1))
		return ;
	ls_glob()->options & (1 << 11) ? files->stat.st_mtime =
		files->stat.st_atime : 0;
	ls_glob()->options & 0b100 && i < 2 ? files->dt |= 8 : 0;
	files->files = S_ISDIR(files->stat.st_mode) && (ls_glob()->options & 1)
	&& !(files->dt & 8)
	? ls_getfiles(files->file_name, &files->file_count, &files->col_width)
	: 0;
}

static void	ls_initfile(t_ls_file **files, char *file_name, char *dir_name)
{
	if (!((*files)->basename = ls_strdup(file_name, 0)))
		exit(0);
	if (!((*files)->file_name = ls_indentjoin(dir_name, "/", file_name,
			0)))
		exit(0);
	(*files)->col_width = 1;
}

t_ls_file	*ls_getfiles(char *dir_name, int *total, short *col_width)
{
	t_ls_file		*file;
	t_ls_file		*head;
	int				i;
	DIR				*dirp;
	struct dirent	*dirent;

	i = !(ls_glob()->options & 0b100) ? -3 : -1;
	if (!(dirp = opendir(dir_name)) && ls_check_error(dir_name, 1))
		return (0);
	!(head = (t_ls_file *)ft_new(sizeof(t_ls_file))) ? exit(0) : 0;
	*head = (t_ls_file){.dt = 1, .col_width = 1};
	while ((dirent = readdir(dirp)) || ls_check_error(0, 0))
	{
		if ((i + 1 < 0 && i++) || (dirent->d_name[0] == '.' &&
					!(ls_glob()->options & 0b1000100)))
			continue ;
		!(file = (t_ls_file *)malloc(sizeof(t_ls_file))) ?
			exit(0) : 0;
		ls_initfile(&file, dirent->d_name, dir_name);
		ls_getdata(file, col_width, ++i);
		ls_sortpush(head, file);
	}
	*total = i + 1;
	closedir(dirp);
	return (head);
}

t_ls_file	*ft_ls(char **dir_names)
{
	t_ls_file	*file;
	t_ls_file	*head;

	!(head = (t_ls_file *)ft_new(sizeof(t_ls_file))) ?
		exit(0) : 0;
	*head = (t_ls_file){.dt = 1};
	while (*dir_names)
	{
		!(file = (t_ls_file *)malloc(sizeof(t_ls_file))) ?
			exit(0) : 0;
		if (lstat(*dir_names, &file->stat) == -1 ||
				!S_ISDIR(file->stat.st_mode))
			ls_check_error(*dir_names, 1);
		file->col_width = 1;
		file->files = ls_getfiles(*dir_names,
				&file->file_count,
				&file->col_width);
		file->file_name = *dir_names;
		file->basename = *dir_names++;
		file->dt |= 4;
		ls_sortpush(head, file);
	}
	head->next ? file->dt |= !head->next->next * 0b10 : 0;
	return (head);
}
