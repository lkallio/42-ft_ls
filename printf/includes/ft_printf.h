/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broccoli <broccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:51:48 by lkallio           #+#    #+#             */
/*   Updated: 2020/08/31 13:32:17 by broccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# include <inttypes.h>
# include <stdlib.h>

typedef struct		s_dt
{
	int		param;
	int		width;
	int		prec;
	int		length;
	int		type;
	int		num_len;
	int		temp;
}					t_dt;

typedef struct		s_pf
{
	t_dt			dt;
	char			buf[1024];
	int				buf_idx;
	int				n;
	const char		*format;
	char			*tempstr;
}					t_pf;

int					handle_double(t_pf *pf, va_list ap);
void				feedbuf_nchar(t_pf *pf, char ins, int n);
void				feedbuf_str(t_pf *pf, char *str, int len);
void				handle_buffer(t_pf *pf, char ins);
int					write_int(uintmax_t in, t_pf *pf, int base, int i);
int					ft_nstrchr(const char *pool, char c);
int					handle_str(t_pf *pf, va_list ap);
int					handle_uint(t_pf *pf, va_list ap);
int					handle_int(t_pf *pf, va_list ap);
int					handle_ptr(t_pf *pf, va_list ap);
int					ft_printf(char const *format, ...);
int					handle_n(t_pf *pf, va_list ap);
int					ft_nstrchr(const char *pool, char c);
int					pf_atoi(t_pf *pf, int *i, int ret);
int					handle_c(t_pf *pf, va_list ap);
int					handle_percent(t_pf *pf);
int					ft_strlen(char *s);
int					handle_longints(t_pf *pf, va_list ap);

#endif
