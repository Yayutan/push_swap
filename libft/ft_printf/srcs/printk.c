/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printk.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 11:52:20 by mchuang           #+#    #+#             */
/*   Updated: 2019/09/28 11:52:21 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*g_w_day[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

static void		put_time(t_buf *buf, int num)
{
	char	*str;

	str = ft_itoa(num);
	if (ft_strlen(str) < 2)
		buf_store_chr(buf, '0');
	buf_store_str(buf, str);
	free(str);
}

char			*initial_k(t_buf *buf, union u_argument u_arg)
{
	struct tm	*arg;

	arg = u_arg.ts;
	if (arg)
	{
		put_time(buf, arg->tm_year + 1900);
		buf_store_chr(buf, '/');
		put_time(buf, arg->tm_mon + 1);
		buf_store_chr(buf, '/');
		put_time(buf, arg->tm_mday);
		buf_store_chr(buf, ' ');
		buf_store_str(buf, g_w_day[arg->tm_wday]);
		buf_store_chr(buf, ' ');
		put_time(buf, arg->tm_hour);
		buf_store_chr(buf, ':');
		put_time(buf, arg->tm_min);
		buf_store_chr(buf, ':');
		put_time(buf, arg->tm_sec);
	}
	return (ft_strnew(0));
}
