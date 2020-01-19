/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printdiouxb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 11:52:08 by mchuang           #+#    #+#             */
/*   Updated: 2019/09/28 11:52:11 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*add_apos(char *s)
{
	char	*to_ret;
	int		i;
	int		j;

	i = 0;
	to_ret = ft_strnew(ft_strlen(s) + (ft_strlen(s) - 1 - i) / 3);
	i = ft_strlen(s) + (ft_strlen(s) - 1 - i) / 3 - 1;
	j = 0;
	to_ret[0] = s[0];
	while (i > 0)
	{
		if (j % 3 == 0 && j != 0)
		{
			to_ret[i--] = ',';
			to_ret[i] = s[ft_strlen(s) - 1 - j];
		}
		else
			to_ret[i] = s[ft_strlen(s) - 1 - j];
		j++;
		i--;
	}
	free(s);
	return (to_ret);
}

int		check_zero(int len, union u_argument u_arg)
{
	if (len == 4 && u_arg.i == 0)
		return (1);
	else if (len == 1 && u_arg.uc == 0)
		return (1);
	else if (len == 2 && u_arg.sh == 0)
		return (1);
	else if (len == 8 && u_arg.lli == 0)
		return (1);
	return (0);
}

char	*do_di(t_spec *sp, union u_argument u_arg)
{
	char			*str;
	char			*tmp;

	str = NULL;
	if (sp->precision == 0 && check_zero(sp->len, u_arg))
		str = ft_strnew(0);
	else if (sp->len == 4)
		str = ft_lltoa_base((int)u_arg.lli, 10);
	else if (sp->len == 1)
		str = ft_lltoa_base((char)u_arg.lli, 10);
	else if (sp->len == 2)
		str = ft_lltoa_base((short)u_arg.lli, 10);
	else if (sp->len == 8)
		str = ft_lltoa_base(u_arg.lli, 10);
	if ((u_arg.lli >> (8 * sp->len - 1)) & 1)
		sp->sign[0] = '-';
	else if (sp->flags[1] || sp->flags[2])
		sp->sign[0] = (sp->flags[1]) ? '+' : ' ';
	if (str[0] == '-')
	{
		tmp = ft_strsub(str, 1, ft_strlen(str) - 1);
		free(str);
		str = tmp;
	}
	return ((sp->flags[5]) ? add_apos(str) : str);
}

char	*do_ouxb(t_spec *sp, union u_argument u_arg)
{
	char	*str;
	int		base;

	str = NULL;
	if (sp->precision == 0 && u_arg.lli == 0)
		return (ft_strnew(0));
	else if (sp->specifier == 'o')
		base = 8;
	else if (ft_strchr("xX", sp->specifier))
		base = 16;
	else if (sp->specifier == 'u')
		base = 10;
	else if (sp->specifier == 'b')
		base = 2;
	if (sp->len == 4)
		str = ft_ulltoa_base((unsigned int)u_arg.i, base);
	else if (sp->len == 1)
		str = ft_ulltoa_base((unsigned char)u_arg.uc, base);
	else if (sp->len == 2)
		str = ft_ulltoa_base((unsigned short)u_arg.sh, base);
	else if (sp->len == 8)
		str = ft_ulltoa_base((unsigned long long int)u_arg.lli, base);
	if (sp->specifier == 'u' && sp->flags[5])
		str = add_apos(str);
	return (str);
}

char	*initial_diouxb(t_spec *sp, union u_argument u_arg)
{
	char	*str;
	char	*tmp;

	if (sp->len == -1 || sp->len == 16)
		sp->len = 4;
	if (check_zero(sp->len, u_arg))
		u_arg.lli = 0;
	if (ft_strchr("di", sp->specifier))
		str = do_di(sp, u_arg);
	else
		str = do_ouxb(sp, u_arg);
	tmp = ft_stradd(str, '0', -1, sp->precision - (int)ft_strlen(str));
	free(str);
	str = tmp;
	if (ft_strchr("bxX", sp->specifier) && u_arg.lli != 0 && sp->flags[3])
	{
		sp->pref[0] = (sp->specifier == 'b') ? 'b' : '0';
		sp->pref[1] = (ft_strchr("xX", sp->specifier)) ? 'x' : '\0';
	}
	else if (sp->specifier == 'o' && sp->flags[3] && str[0] != '0')
		sp->pref[0] = '0';
	return (str);
}
