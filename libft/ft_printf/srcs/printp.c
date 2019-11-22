/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 11:52:24 by mchuang           #+#    #+#             */
/*   Updated: 2019/09/28 11:52:26 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*initial_p(t_spec *sp, union u_argument u_arg)
{
	char			*str;
	char			*address;
	long long int	arg;

	arg = u_arg.lli;
	if (arg == 0 && sp->precision == 0)
		address = ft_strnew(0);
	else
		address = ft_ulltoa_base(arg, 16);
	str = ft_stradd(address, '0', -1, sp->precision - ft_strlen(address));
	free(address);
	address = ft_strjoin("0x", str);
	free(str);
	return (address);
}
