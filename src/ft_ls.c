/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broccoli <broccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 17:32:46 by broccoli          #+#    #+#             */
/*   Updated: 2020/08/25 13:32:25 by broccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			main(int ac, char **av)
{
	static char	ops[] = {"Rlat1dAfCSru0BFGHLOPTUWbceghikmnopqswx"};
	static char	*this_dir[2] = {".", 0};
	int			ret;
	t_ls_file	*files;

	ls_glob()->options = 0;
	if (ac > 1 && *(++av) && **av == '-')
	{
		while (*++(*av))
		{
			if ((ret = ft_strnchr(ops, **av)) == -1)
				print_usage(*av);
			ls_glob()->options |= ret <= 32 ? (1 << ret) : 0;
		}
		++av;
		--ac;
	}
	ls_glob()->options & (1 << 7) ? ls_glob()->options |= (1 << 2) : 0;
	files = ft_ls(--ac ? av : this_dir);
	ls_dirprint(files->next, 0);
	ls_glob()->options & (1 << 12) ? ft_printf("%d\n",
			ls_glob()->file_count) : 0;
	return (0);
}
