/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_step.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 21:04:41 by mchuang           #+#    #+#             */
/*   Updated: 2020/01/09 21:04:43 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		final_ord(t_ps *ps)
{
	int		pt;
	int		gp;
	int		n_sym;
	int		i;

	pt = 0;
	if (ps->max_symbols == 5)
		gp = 1;
	else
		gp = 0;
	i = 0;
	while (pt < ps->n_parts)
	{
		n_sym = 0;
		while (n_sym < ps->sym_p_pt && i >= 0 && i < ps->len)
		{
			ps->sorted[i++]->group = gp;
			n_sym++;
		}
		gp++;
		pt++;
	}
}

void		final_ord_rev(t_ps *ps)
{
	int		pt;
	int		gp;
	int		n_sym;
	int		i;

	pt = 0;
	if (ps->max_symbols == 5)
		gp = 1;
	else
		gp = 0;
	i = ps->len - 1;
	while (pt < ps->n_parts)
	{
		n_sym = 0;
		while (n_sym < ps->sym_p_pt && i >= 0 && i < ps->len)
		{
			ps->sorted[i--]->group = gp;
			n_sym++;
		}
		gp++;
		pt++;
	}
}
