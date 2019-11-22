/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_proc_fin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 11:58:33 by mchuang           #+#    #+#             */
/*   Updated: 2019/09/28 11:58:36 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char				*finalize(t_spec *sp, char *str)
{
	char	*tmp;
	int		to_pad;

	to_pad = sp->width - (int)ft_strlen(str);
	to_pad -= (int)(ft_strlen(sp->pref) + ft_strlen(sp->sign));
	if ((!ft_strchr("diouxXb", sp->specifier) || sp->precision < 0)
		&& sp->flags[4] && !sp->flags[0])
	{
		tmp = ft_stradd(str, '0', -1, to_pad);
		free(str);
		str = tmp;
	}
	tmp = ft_strjoin(sp->pref, str);
	free(str);
	str = ft_strjoin(sp->sign, tmp);
	free(tmp);
	if (sp->flags[0])
		tmp = ft_stradd(str, ' ', 1, sp->width - (int)ft_strlen(str));
	else
		tmp = ft_stradd(str, ' ', -1, sp->width - (int)ft_strlen(str));
	free(str);
	str = (ft_strchr("XEG", sp->specifier)) ? ft_strup(tmp) : tmp;
	return (str);
}

union u_argument	setup_arg(t_spec *sp, t_args *arg_lst)
{
	union u_argument	u_arg;

	u_arg.str = "-42";
	if (sp->specifier != '%' && sp->param == 0)
	{
		u_arg = next_arg(sp->arg, sp->param_lst);
		sp->arg = (sp->arg)->next;
	}
	else if (sp->specifier != '%')
	{
		va_end(sp->param_lst);
		va_copy(sp->param_lst, sp->orig);
		u_arg = nth_arg_sp(arg_lst, sp->param, sp->param_lst);
		sp->arg = arg_lst_at(arg_lst, sp->param);
	}
	return (u_arg);
}

/*
** Function that forms the output to put in the buffer
** First finds the next parameter, then distributes initial string processing
** functions according to the sp, then adds padding, signs, etc. to form the
** final string.
** Returns the final result of the output for the sp given.
*/

char				*d_p_f(t_buf *buf, t_spec *sp, t_args *arg_lst)
{
	char				*to_ret;
	union u_argument	u_arg;

	u_arg = setup_arg(sp, arg_lst);
	if (sp->specifier == 'c')
		return (initial_c(sp, buf, u_arg));
	else if (sp->specifier == 's')
		to_ret = initial_s(sp, u_arg);
	else if (ft_strchr("diouxXb", sp->specifier))
		to_ret = initial_diouxb(sp, u_arg);
	else if (ft_strchr("fFeEgG", sp->specifier))
		to_ret = initial_feg(sp, u_arg);
	else if (sp->specifier == 'k')
		return (initial_k(buf, u_arg));
	else if (sp->specifier == 'p')
		to_ret = initial_p(sp, u_arg);
	else if (sp->specifier == '%')
		to_ret = ft_strdup("%");
	else
		return (NULL);
	return (finalize(sp, to_ret));
}

char				*i_f(t_spec *sp, char *format, int *i)
{
	char	*to_ret;
	int		j;

	j = *i;
	while (format[*i] && format[*i] != '%')
		(*i)++;
	to_ret = ft_strsub(format, j, *i - j);
	return (finalize(sp, to_ret));
}
