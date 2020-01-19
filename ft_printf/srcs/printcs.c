/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printcs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 11:51:56 by mchuang           #+#    #+#             */
/*   Updated: 2019/09/28 11:52:05 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*initial_c(t_spec *sp, t_buf *buf, union u_argument u_arg)
{
	char			*str;
	unsigned char	n_c;

	n_c = u_arg.uc;
	if (sp->flags[4] && !sp->flags[0])
		str = ft_stradd("", '0', -1, sp->width - 1);
	else
		str = ft_stradd("", ' ', -1, sp->width - 1);
	if (sp->flags[0])
	{
		buf_store_chr(buf, n_c);
		buf_store_str(buf, str);
	}
	else
	{
		buf_store_str(buf, str);
		buf_store_chr(buf, n_c);
	}
	free(str);
	return (ft_strnew(0));
}

char	*initial_s(t_spec *sp, union u_argument u_arg)
{
	char	*str;
	char	*n_s;
	int		nd_free;

	n_s = u_arg.str;
	if (!n_s)
	{
		nd_free = 1;
		n_s = ft_strdup("(null)");
	}
	else
		nd_free = 0;
	if (sp->precision < 0)
		str = ft_strdup(n_s);
	else
		str = ft_strsub(n_s, 0, sp->precision);
	if (nd_free)
		free(n_s);
	return (str);
}
