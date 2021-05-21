/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broccoli <broccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 18:35:16 by broccoli          #+#    #+#             */
/*   Updated: 2020/08/31 13:30:34 by broccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/ioctl.h>
# include <pwd.h>
# include <grp.h>
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include <stdlib.h>
# include "ft_printf.h"
# include <time.h>
# include <sys/acl.h>
# include <string.h>
# include <errno.h>

# define LS_SIXMONTHS	15778476

typedef struct			s_ls_file
{
	struct stat			stat;
	char				*file_name;
	char				*basename;
	short				name_len;
	short				dt;
	struct s_ls_file	*files;
	struct s_ls_file	*next;
	int					file_count;
	short				col_width;
}						t_ls_file;

typedef struct			s_lf_data
{
	short				nlink_width;
	short				nm_width;
	short				gr_width;
	short				fs_width;
	short				maj_width;
	short				min_width;
	blkcnt_t			block_count;
}						t_lf_data;

typedef struct			s_ls_glob
{
	struct passwd		*pwd;
	struct group		*grp;
	t_lf_data			lf;
	short				win_width;
	short				col_width;
	short				file_count;
	short				longest_name;
	short				cols;
	short				rows;
	int					options;
}						t_ls_glob;

t_ls_file				*ls_getfiles(char *dir_name, int
		*total, short *col_width);
t_ls_file				*ft_ls(char **dir_names);
void					*ls_realloc(void *addr, size_t size,
		size_t mem_size, size_t increment);
int						ft_strnchr(char *str, char c);
char					*ls_strdup(char *src, int i);
void					ft_strcpy(char *d, char *s);
int						ft_numlen(int n);
void					*ls_realloc(void *addr, size_t size,
		size_t mem_size, size_t increment);
char					*ls_indentjoin(char *s, char *slash, char *ss, int i);
t_ls_glob				*ls_glob();
void					print_usage(char *option);
void					ls_exit(char *name);
void					ls_dirprint(t_ls_file *files, int is_rec);
char					ls_filetype(int data);
char					*ls_permissions(int data);
char					*ls_lnksuffix(t_ls_file *files);
void					ls_lfdata(t_ls_file *files);
void					ft_putnchar(char *s, int n);
void					*ft_new(size_t size);
int						ls_comparison(t_ls_file *filea, t_ls_file *fileb);
int						ls_xattr(char *path);
int						ls_check_error(char *basename, int ret);
int						ft_strcmp(char *sa, char *sb);
t_ls_file				*nth_file(t_ls_file *files, int n);

#endif
