/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broccoli <broccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 17:37:44 by broccoli          #+#    #+#             */
/*   Updated: 2020/08/31 13:28:57 by broccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_putnchar(char *s, int n)
{
	if (n <= 0)
		return ;
	ft_printf(s);
	ft_putnchar(s, n - 1);
}

int			ft_numlen(int n)
{
	return (n / 10 ? 1 + ft_numlen(n / 10) : 1);
}

void		*ft_new(size_t size)
{
	void	*ret;

	ret = malloc(size);
	while (ret && size--)
		((unsigned char *)ret)[size] = 0;
	return (ret);
}

int			ls_comparison(t_ls_file *filea, t_ls_file *fileb)
{
	int	ret;

	if (ls_glob()->options & (1 << 9))
		ret = filea->stat.st_size <= fileb->stat.st_size;
	else if (ls_glob()->options & (1 << 3))
		ret = filea->stat.st_mtime <= fileb->stat.st_mtime;
	else
		ret = ft_strcmp(filea->basename, fileb->basename) >= 0;
	return (ret + !!(ls_glob()->options & (1 << 10)) == 1);
}

t_ls_file	*nth_file(t_ls_file *files, int n)
{
	while (files->next && n--)
		files = files->next;
	return (files);
}
