/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_exceptions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broccoli <broccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 13:28:43 by broccoli          #+#    #+#             */
/*   Updated: 2020/08/25 13:34:08 by broccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_usage(char *option)
{
	ft_printf("ft_ls: illegal option -- %s\nusage: ./ft_ls ", option);
	ft_printf("[-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx10] ");
	ft_printf("[file ...]\n");
	exit(0);
}

void		ls_exit(char *name)
{
	ft_printf("ls: %s: No such file or directory\n", name);
	exit(0);
}

int			ls_check_error(char *basename, int ret)
{
	if (errno)
		ft_printf("%s%s%s%s\n", "ft_ls: ", basename, basename ? ": " :
			"", strerror(errno));
	errno = 0;
	return (ret);
}
