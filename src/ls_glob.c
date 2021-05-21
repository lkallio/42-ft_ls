/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_glob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broccoli <broccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 17:32:46 by broccoli          #+#    #+#             */
/*   Updated: 2020/08/25 13:32:33 by broccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls_glob		*ls_glob(void)
{
	static t_ls_glob	glob[1] = {{.col_width = 1}};
	struct winsize		ws;

	if (!glob->win_width)
	{
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 ? ws.ws_col = 10 :
			0;
		glob->win_width = ws.ws_col;
	}
	return (glob);
}
