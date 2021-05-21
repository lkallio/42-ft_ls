/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 17:55:07 by broccoli          #+#    #+#             */
/*   Updated: 2021/05/21 16:00:25 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			ls_writesize(t_ls_file *files)
{
	if (S_ISBLK(files->stat.st_mode) || S_ISCHR(files->stat.st_mode))
		ft_printf(" %*d, %*d", ls_glob()->lf.maj_width,
				major(files->stat.st_rdev),
				ls_glob()->lf.min_width,
				minor(files->stat.st_rdev));
	else
		ft_printf("%*zu", ls_glob()->lf.fs_width, files->stat.st_size);
}

static void			ls_lfprint(t_ls_file *files)
{
	static char	buffer[1024];
	char		*lf_time;
	short		timediff;

	if (!(lf_time = ctime(&files->stat.st_mtime)))
		exit(0);
	timediff = files->stat.st_mtime < time(0) - LS_SIXMONTHS ||
		files->stat.st_mtime > time(0) + LS_SIXMONTHS;
	lf_time[24] = 0;
	ft_printf("%c%s%c %*d %-*s%-*s",
			ls_filetype(files->stat.st_mode),
			ls_permissions(files->stat.st_mode),
			ls_xattr(files->file_name), ls_glob()->lf.nlink_width,
			files->stat.st_nlink, ls_glob()->lf.nm_width
			+ 2, getpwuid(files->stat.st_uid)->pw_name,
			ls_glob()->lf.gr_width + 2,
			getgrgid(files->stat.st_gid)->gr_name);
	ls_writesize(files);
	ft_printf(" %6.6s %5.5s %s%s\n", lf_time + 4,
			lf_time + 11 + timediff * 9,
			files->basename, S_ISLNK(files->stat.st_mode) ?
			ls_lnksuffix(files) : "");
	*buffer = 0;
	if (files->next)
		ls_lfprint(files->next);
}

static void			ls_lf(t_ls_file *files)
{
	ls_lfdata(files->files->next);
	ft_printf("total %d\n", ls_glob()->lf.block_count);
	ls_glob()->lf.fs_width < ls_glob()->lf.maj_width +
		ls_glob()->lf.min_width ? ls_glob()->lf.fs_width =
		ls_glob()->lf.maj_width + ls_glob()->lf.min_width + 3 : 0;
	ls_lfprint(files->files->next);
	ls_glob()->lf = (t_lf_data){0};
}

static void			ls_regprint(t_ls_file *files, int start, int file_count)
{
	int	i;

	i = -1;
	while (++i < ls_glob()->cols && start + i * ls_glob()->rows <= file_count)
	{
		i ? ft_putnchar("\t", ls_glob()->col_width - (nth_file(files, start + (i
						- 1) *
					ls_glob()->rows)->name_len / 8)) : 0;
		ft_printf(nth_file(files, start + i * ls_glob()->rows)->basename);
	}
	ft_printf("\n");
	start < ls_glob()->rows ? ls_regprint(files, start + 1, file_count) : 0;
}

void				ls_dirprint(t_ls_file *files, int is_rec)
{
	int		i;

	if (!files)
		return;
	i = 1;
	if (S_ISDIR(files->stat.st_mode) && !(files->dt & 0b1010) &&
			((files->dt & 4) || ls_glob()->options & 1))
		ft_printf("%s%s:\n", is_rec ? "\n" : "", files->file_name);
	if (files->files)
	{
		if (ls_glob()->options & 2)
			ls_lf(files);
		else
		{
			ls_glob()->cols = ls_glob()->win_width / (8 *
					files->col_width);
			ls_glob()->cols += !ls_glob()->cols + (ls_glob()->cols
					< 2 && ls_glob()->options & (1 << 8));
			ls_glob()->rows = files->file_count / ls_glob()->cols +
				!!(files->file_count % ls_glob()->cols);
			ls_glob()->col_width = files->col_width;
			ls_regprint(files->files, 1, files->file_count);
		}
		ls_dirprint(files->files->next, 1);
	}
	if (files->next)
		ls_dirprint(files->next, 1);
}
