/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:50:50 by lkallio           #+#    #+#             */
/*   Updated: 2020/02/14 11:22:27 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_strlen(char *s)
{
	return (!s || !*s ? 0 : 1 + ft_strlen(s + 1));
}

int		ft_nstrchr(const char *pool, char c)
{
	int		i;

	i = -1;
	while (pool[++i])
		if (pool[i] == c)
			return (i);
	return (-1);
}

int		pf_atoi(t_pf *pf, int *i, int ret)
{
	if (pf->format[(*i)] >= '0' && pf->format[(*i)] <= '9')
	{
		ret = ret * 10 + pf->format[(*i)++] - '0';
		return (pf_atoi(pf, i, ret));
	}
	return (ret);
}
