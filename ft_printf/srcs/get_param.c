/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:22:17 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/14 23:58:15 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					check_ptr_type(va_list param)
{
	va_list	test;
	int		tst;

	va_copy(test, param);
	tst = (va_arg(test, char*) != NULL);
	if (!tst)
		va_arg(param, char*);
	va_end(test);
	return (tst);
}

/*
** Function that sets the argument union from the information
** provided in argument node arg.
*/

union u_argument	next_arg(t_args *arg, va_list param)
{
	union u_argument	next;

	next.lli = 0;
	if (!arg || (ft_strchr("fFks", arg->size) && !check_ptr_type(param)))
		return (next);
	if (ft_strchr("crH", arg->size))
		next.uc = (unsigned char)va_arg(param, int);
	else if (arg->size == 's')
		next.str = va_arg(param, char*);
	else if (arg->size == 'f')
		next.d = va_arg(param, double);
	else if (arg->size == 'F')
		next.ld = va_arg(param, long double);
	else if (arg->size == 'i')
		next.i = va_arg(param, int);
	else if (arg->size == 'h')
		next.sh = (short)va_arg(param, int);
	else if (arg->size == 'l')
		next.li = va_arg(param, long int);
	else if (arg->size == 'L' || arg->size == 'p')
		next.lli = va_arg(param, long long int);
	else if (arg->size == 'k')
		next.ts = va_arg(param, struct tm*);
	return (next);
}

/*
** Function that sets the argument union of the nth node argument list
** Copies from the original va_list
*/

union u_argument	nth_arg_orig(t_args *arg, int n, va_list orig)
{
	int					i;
	t_args				*cur;
	va_list				cp;
	union u_argument	next;

	next.str = "";
	i = 1;
	cur = arg;
	va_copy(cp, orig);
	while (cur && i <= n)
	{
		next = next_arg(cur, cp);
		i++;
		cur = cur->next;
	}
	va_end(cp);
	return (next);
}

/*
** Function that sets the argument union of the nth node argument list
** Changes the provided va_list
*/

union u_argument	nth_arg_sp(t_args *arg, int n, va_list sp)
{
	int					i;
	t_args				*cur;
	union u_argument	next;

	next.str = "";
	i = 1;
	cur = arg;
	while (cur && i <= n)
	{
		next = next_arg(cur, sp);
		i++;
		cur = cur->next;
	}
	return (next);
}
