/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 18:35:23 by mchuang           #+#    #+#             */
/*   Updated: 2019/10/26 18:35:26 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Setting up a new argument node depending on whether we encounter a
** specifier character.
** NOTE: The length char l preceeds the char h
** Returns 0 if no valid spec char is found
** Adds new node to arg list and returns 1 if valid spec is found
*/

int		spec_arg(t_args **arg, char sp, int *n_l, int *nxt_arg)
{
	if (ft_strchr("dDioOuUxXbBfFeEgGcsprk%", sp))
	{
		if (ft_strchr("csprk", sp))
			*arg = insert_arg(*arg, new_arg(*nxt_arg, sp));
		else if (ft_strchr("fFeEgG", sp))
		{
			*arg = insert_arg(*arg, new_arg(*nxt_arg, 'f'));
			if (n_l[2] == 1)
				*arg = insert_arg(*arg, new_arg(*nxt_arg, 'F'));
		}
		else if (ft_strchr("dDioOUuxXbB", sp))
		{
			*arg = insert_arg(*arg, new_arg(*nxt_arg, 'i'));
			if (n_l[0] == 1 || ft_strchr("DOU", sp))
				*arg = insert_arg(*arg, new_arg(*nxt_arg, 'l'));
			else if (n_l[0] == 2)
				*arg = insert_arg(*arg, new_arg(*nxt_arg, 'L'));
			else if (n_l[1] == 1)
				*arg = insert_arg(*arg, new_arg(*nxt_arg, 'h'));
			else if (n_l[1] == 2)
				*arg = insert_arg(*arg, new_arg(*nxt_arg, 'H'));
		}
		return (1);
	}
	return (0);
}

/*
** Setting up a new argument node when we see '*' in ft.
** Possible cases include:
** * -> get next argument (nxt_arg++)
** *n -> still gets next argument, and don't worry about n (nxt_arg++)
** *n$ -> nth parameter is an int (doesn't affect nxt_arg)
** Returns the index of the next char to look at in ft
*/

int		star_arg(t_args **arg, char *ft, int i, int *nxt_arg)
{
	int		num;

	if (ft[i] >= '0' && ft[i] <= '9')
	{
		num = ft_atoi(ft + i);
		while (ft[i] >= '0' && ft[i] <= '9')
			i++;
		if (ft[i] == '$')
			*arg = insert_arg(*arg, new_arg(num, 'i'));
		else
		{
			*arg = insert_arg(*arg, new_arg(*nxt_arg, 'i'));
			(*nxt_arg)++;
		}
	}
	else if (ft[i] != '$')
	{
		*arg = insert_arg(*arg, new_arg(*nxt_arg, 'i'));
		(*nxt_arg)++;
	}
	i += (ft[i] != '$') ? 0 : 1;
	return (i);
}

/*
** Setting up a new argument node when we see numbers in ft.
** Possible cases include:
** n -> probably fixed width, nothing needs to be done
** n$c -> if c is a valid specifier, add node to list and set nxt_arg to num+1
** (Due to norm) Returns the increment in index to the next char to look at
*/

int		num_arg(t_args **arg, char *ft, int *n_l, int *nxt_arg)
{
	int		num;
	int		j;

	num = ft_atoi(ft);
	j = 0;
	while (ft[j] && ft[j] >= '0' && ft[j] <= '9')
		j++;
	if (ft[j] == '$')
	{
		j++;
		if (ft[j] && spec_arg(arg, ft[j], n_l, &num))
		{
			j++;
			*nxt_arg = num + 1;
		}
	}
	return (j);
}

/*
** Sets up the length array depending on the character read.
*/

void	len_format(char ft, int *n_l)
{
	if (ft == 'l')
		n_l[0] += (n_l[0] == 2) ? 0 : 1;
	else if (ft == 'h')
		n_l[1] = (n_l[1] == 1) ? 2 : 1;
	else if (ft == 'j' || ft == 'z')
		n_l[0] = 2;
	else if (ft == 'L')
		n_l[2] = 1;
}

/*
** Looks through a "set" of format and set up new arguments
** If we find numbers, '*', specifiers, we need to check and set up nodes.
** We also need to keep track of length charactes(l,h,L), since they affect
** the final type of the argument as well.
** n_l[i]-> 0:l, 1:h, 2:L
** Returns the next index to look at past this set of format.
*/

int		add_arg_info(char *ft, int i, t_args **arg, int *nxt_arg)
{
	int n_l[3];

	ft_bzero(n_l, sizeof(n_l));
	while (ft[i] && ft_strchr(",;:_vaACSnjz0123456789hlL*.'#-+ ", ft[i]))
	{
		if (ft[i] >= '1' && ft[i] <= '9')
		{
			i += num_arg(arg, ft + i, n_l, nxt_arg);
			if (ft_strchr("dDioOuUxXbBfFeEgGcsprk%", ft[i - 1]))
				return (i);
		}
		else if (ft[i] == '*')
			i = star_arg(arg, ft, i + 1, nxt_arg);
		else
			len_format(ft[i++], n_l);
	}
	if (spec_arg(arg, ft[i], n_l, nxt_arg))
	{
		i++;
		(*nxt_arg)++;
	}
	return (i);
}
