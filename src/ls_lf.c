/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broccoli <broccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 17:43:32 by broccoli          #+#    #+#             */
/*   Updated: 2020/08/31 13:29:55 by broccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		ls_filetype(int data)
{
	if (S_ISLNK(data))
		return ('l');
	if (S_ISFIFO(data))
		return ('p');
	if (S_ISDIR(data))
		return ('d');
	if (S_ISBLK(data))
		return ('b');
	if (S_ISSOCK(data))
		return ('s');
	if (S_ISCHR(data))
		return ('c');
	return ('-');
}

char		*ls_permissions(int data)
{
	static char		letters[3] = {"rwx"};
	static char		out[10];
	char			*temp;
	int				idf;
	int				i;

	i = 0;
	idf = 0000400;
	temp = out;
	while (idf)
	{
		*temp = data & idf ? letters[i % 3] : '-';
		if ((i == 2 && (S_ISUID & data)) || (i == 5 && (S_ISGID & data)))
			*temp = *temp == letters[i % 3] ? 's' : 'S';
		if (i == 8 && (S_ISVTX & data))
			*temp = *temp == letters[i % 3] ? 't' : 'T';
		i++;
		temp++;
		idf /= 2;
	}
	*temp = 0;
	return (out);
}

char		*ls_lnksuffix(t_ls_file *files)
{
	static char	buffer[1028] = " -> ";
	int			len;

	if ((len = readlink(files->file_name, buffer + 4, 1024)) == -1)
		return (0);
	buffer[len + 4] = 0;
	return (buffer);
}

void		ls_lfdata(t_ls_file *files)
{
	static t_lf_data	lf_new;
	int					i;

	lf_new = (t_lf_data) {ft_numlen(files->stat.st_nlink),
		ft_strlen(getpwuid(files->stat.st_uid)->pw_name),
		ft_strlen(getgrgid(files->stat.st_gid)->gr_name),
		ft_numlen(files->stat.st_size),
		ft_numlen(major(files->stat.st_rdev)),
		ft_numlen(minor(files->stat.st_rdev)), 0};
	i = -1;
	while (++i < 6)
		*((short *)&lf_new + i) > *((short *)&ls_glob()->lf + i) ?
			*((short *)&ls_glob()->lf + i) = *((short *)&lf_new + i) : 0;
	ls_glob()->lf.block_count += files->stat.st_blocks;
	if (files->next)
		ls_lfdata(files->next);
}

int			ls_xattr(char *path)
{
	static char	buffer[1024];
	acl_t		acl;

	if (listxattr(path, buffer, 1024, XATTR_NOFOLLOW) > 0)
		return ('@');
	else if ((acl = acl_get_link_np(path, ACL_TYPE_EXTENDED)))
	{
		acl_free(acl);
		return ('+');
	}
	return (' ');
}
