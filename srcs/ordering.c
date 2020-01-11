/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ordering.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 03:29:39 by mchuang           #+#    #+#             */
/*   Updated: 2020/01/11 03:29:41 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		set_one_group_a(t_ps *ps, int i, int ord)
{
	int		gp;
	int		sym_put;

	gp = 0;
	while (gp < ps->max_symbols)
	{
		sym_put = 0;
		while (sym_put < ps->sym_p_pt && i >= 0 && i < ps->len)
		{
			ps->sorted[i]->group = (ord == 1) ? gp : (ps->max_symbols - 1 - gp);
			sym_put++;
			i++;
		}
		gp++;
	}
	return (i);
}

static int		fill_to_a(t_ps *ps, int i, int layer, int ord)
{
	if (layer <= log_m_ceil(ps->sym_p_pt, ps->max_symbols))
		i = set_one_group_a(ps, i, ord);
	else if (ord == 1)
	{
		if (ps->max_symbols == 5)
			i = fill_to_a(ps, i, layer - 1, -1);
		i = fill_to_a(ps, i, layer - 1, -1);
		i = fill_to_a(ps, i, layer - 1, -1);
		i = fill_to_a(ps, i, layer - 1, 1);
		i = fill_to_a(ps, i, layer - 1, 1);
	}
	else if (ord == -1)
	{
		i = fill_to_a(ps, i, layer - 1, -1);
		i = fill_to_a(ps, i, layer - 1, -1);
		i = fill_to_a(ps, i, layer - 1, 1);
		i = fill_to_a(ps, i, layer - 1, 1);
		if (ps->max_symbols == 5)
			i = fill_to_a(ps, i, layer - 1, 1);
	}
	return (i);
}

static int		set_one_group_b(t_ps *ps, int i, int ord)
{
	int		gp;
	int		sym_put;

	gp = 0;
	while (gp < ps->max_symbols)
	{
		sym_put = 0;
		while (sym_put < ps->sym_p_pt && i >= 0 && i < ps->len)
		{
			ps->sorted[i]->group = (ord == 1) ? (ps->max_symbols - 1 - gp) : gp;
			sym_put++;
			i--;
		}
		gp++;
	}
	return (i);
}

static int		fill_to_b(t_ps *ps, int i, int layer, int ord)
{
	if (layer <= log_m_ceil(ps->sym_p_pt, ps->max_symbols))
		i = set_one_group_b(ps, i, ord);
	else if (ord == 1)
	{
		i = fill_to_b(ps, i, layer - 1, 1);
		i = fill_to_b(ps, i, layer - 1, 1);
		i = fill_to_b(ps, i, layer - 1, -1);
		i = fill_to_b(ps, i, layer - 1, -1);
		if (ps->max_symbols == 5)
			i = fill_to_b(ps, i, layer - 1, -1);
	}
	else if (ord == -1)
	{
		if (ps->max_symbols == 5)
			i = fill_to_b(ps, i, layer - 1, 1);
		i = fill_to_b(ps, i, layer - 1, 1);
		i = fill_to_b(ps, i, layer - 1, 1);
		i = fill_to_b(ps, i, layer - 1, -1);
		i = fill_to_b(ps, i, layer - 1, -1);
	}
	return (i);
}

void			update_index(t_ps *ps, int end_b)
{
	int		i;
	int		pt;
	int		mid;

	mid = ps->n_parts / 2 + (ps->n_parts % 2);
	i = (end_b) ? (ps->len - 1) : 0;
	pt = 0;
	while (pt < mid)
	{
		if (end_b)
			i = fill_to_b(ps, i, ps->layer, 1);
		else
			i = fill_to_a(ps, i, ps->layer, -1);
		pt++;
	}
	while (pt < ps->n_parts)
	{
		if (end_b)
			i = fill_to_b(ps, i, ps->layer, -1);
		else
			i = fill_to_a(ps, i, ps->layer, 1);
		pt++;
	}
}
