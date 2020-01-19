/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 01:50:40 by mchuang           #+#    #+#             */
/*   Updated: 2019/10/17 01:50:42 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "pow_of_two.h"

/*
** Function that calculates the exponent(base 2) of a long double.
** Extracts information in the bits of the number, and adds on each part of the
** exponent.
*/

int		get_ld_exp(union u_ldouble u_ld)
{
	int		exp;
	int		i;

	exp = 0;
	i = 0;
	while (i <= 7)
	{
		exp += (((u_ld.data[8] >> i) & 1) << i);
		i++;
	}
	while (i <= 14)
	{
		exp += (((u_ld.data[9] >> (i - 8)) & 1) << i);
		i++;
	}
	return (exp - 16383);
}

/*
** Function that calculates the mantissa of a double.
** Adds on the base 10 form of 2's negative power whenever the bit is on.
** Also records the whether the mantissa is 0 (for reserved values).
** Result is stored in char *m, in base 10.
*/

int		get_d_mantissa(union u_double u_d, char *m)
{
	int	i;
	int	sh;
	int	p;
	int zero;

	zero = 0;
	add(m, g_pow_two[1][0]);
	p = 1;
	i = 6;
	sh = 3;
	while (p <= 52)
	{
		while (sh >= 0)
		{
			if ((u_d.data[i] >> sh) & 1)
				add(m, g_pow_two[1][p]);
			if ((u_d.data[i] >> sh) & 1)
				zero = 1;
			p++;
			sh--;
		}
		i--;
		sh = 7;
	}
	return (zero);
}

/*
** Function that calculates the mantissa of a long double.
** Adds on the base 10 form of 2's negative power whenever the bit is on.
** Also records the whether the mantissa is 0 (for reserved values).
** Result is stored in char *m, in base 10.
*/

int		get_ld_mantissa(union u_ldouble u_ld, char *m)
{
	int	i;
	int	sh;
	int	p;
	int	zero;

	p = 0;
	i = 7;
	zero = 0;
	while (p <= 63)
	{
		sh = 7;
		while (sh >= 0)
		{
			if ((u_ld.data[i] >> sh) & 1)
			{
				add(m, g_pow_two[1][p]);
				if (p)
					zero = 1;
			}
			p++;
			sh--;
		}
		i--;
	}
	return (zero);
}

/*
** Function that decides the next pow of 2 to multiply on mantissa
*/

int		next_exp(int e)
{
	if (e >= 4096)
		return (4096);
	else if (e >= 2048)
		return (2048);
	else if (e >= 1024)
		return (1024);
	else if (e >= 512)
		return (512);
	else if (e >= 256)
		return (256);
	else if (e >= 64)
		return (64);
	else
		return (e);
}

/*
** Function that calculates the correct form of the mantissa after adding
** up the digits from the mantissa bits.
** Resulting string is res*2^e
*/

int		shift_mantissa(char *res, int e)
{
	int	sh;
	int	p;
	int	neg;

	neg = (e < 0);
	e = (neg) ? -1 * e : e;
	sh = (neg) ? e : 0;
	while (e != 0)
	{
		p = next_exp(e);
		if (p == 4096)
			mult(res, ft_strtrimc(g_pow_two[neg][69], '0'));
		else if (p == 2048)
			mult(res, ft_strtrimc(g_pow_two[neg][68], '0'));
		else if (p == 1024)
			mult(res, ft_strtrimc(g_pow_two[neg][67], '0'));
		else if (p == 512)
			mult(res, ft_strtrimc(g_pow_two[neg][66], '0'));
		else if (p == 256)
			mult(res, ft_strtrimc(g_pow_two[neg][65], '0'));
		else
			mult(res, ft_strtrimc(g_pow_two[neg][p], '0'));
		e -= p;
	}
	return (sh);
}
