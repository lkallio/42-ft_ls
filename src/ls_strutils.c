/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_strutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broccoli <broccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 17:32:46 by broccoli          #+#    #+#             */
/*   Updated: 2020/08/31 13:29:42 by broccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*ls_indentjoin(char *s, char *slash, char *ss, int i)
{
	char	*out;

	if (*s && (out = ls_indentjoin(s + 1, slash, ss, i + 1)))
		out[i] = *s;
	else if (*slash && (out = ls_indentjoin(s, slash + 1, ss, i + 1)))
		out[i] = *slash;
	else if (*ss && (out = ls_indentjoin(s, slash, ss + 1, i + 1)))
		out[i] = *ss;
	else
	{
		if (!(out = (char *)malloc(i + 1)))
			exit(0);
		out[i] = 0;
	}
	return (out);
}

int			ft_strnchr(char *str, char c)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}

char		*ls_strdup(char *src, int i)
{
	char	*out;

	if (*src)
	{
		out = ls_strdup(src + 1, i + 1);
		out[i] = *src;
	}
	else
	{
		if (!(out = (char *)malloc(i + 1)))
			exit(0);
		out[i] = 0;
	}
	return (out);
}

void		ft_strcpy(char *d, char *s)
{
	(*d = *s) ? ft_strcpy(d + 1, s + 1) : 0;
}

int			ft_strcmp(char *sa, char *sb)
{
	if (*sa != *sb)
		return (*sa - *sb);
	return (*sa ? ft_strcmp(sa + 1, sb + 1) : 0);
}
