/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 20:30:24 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/24 20:30:41 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		log_m_ceil(int n, int m)
{
	int		log;
	int		cur;

	log = 0;
	cur = 1;
	while (cur < n)
	{
		cur *= m;
		log++;
	}
	return (log);
}

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
	if (layer <= 1)
		i = set_one_group_a(ps, i, ord);
	else if (ord == 1)
	{
		fill_to_a(ps, i, layer - 1, -1);
		fill_to_a(ps, i, layer - 1, -1);
		fill_to_a(ps, i, layer - 1, -1);
		fill_to_a(ps, i, layer - 1, 1);
		fill_to_a(ps, i, layer - 1, 1);
	}
	else if (ord == 1)
	{
		fill_to_a(ps, i, layer - 1, -1);
		fill_to_a(ps, i, layer - 1, -1);
		fill_to_a(ps, i, layer - 1, 1);
		fill_to_a(ps, i, layer - 1, 1);
		fill_to_a(ps, i, layer - 1, 1);
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
			ps->sorted[i]->group = (ord == 1) ? gp : (ps->max_symbols - 1 - gp);
			sym_put++;
			i--;
		}
		gp++;
	}
	return (i);
}

static int		fill_to_b(t_ps *ps, int i, int layer, int ord)
{
	if (layer <= 1)
		i = set_one_group_b(ps, i, ord);
	else if (ord == 1)
	{
		fill_to_b(ps, i, layer - 1, 1);
		fill_to_b(ps, i, layer - 1, 1);
		fill_to_b(ps, i, layer - 1, -1);
		fill_to_b(ps, i, layer - 1, -1);
		fill_to_b(ps, i, layer - 1, -1);
	}
	else if (ord == 1)
	{
		fill_to_b(ps, i, layer - 1, 1);
		fill_to_b(ps, i, layer - 1, 1);
		fill_to_b(ps, i, layer - 1, 1);
		fill_to_b(ps, i, layer - 1, -1);
		fill_to_b(ps, i, layer - 1, -1);
	}
	return (i);
}

static void		update_index(t_ps *ps, int a_to_b, int end_b)
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
		{
			i = fill_to_b(ps, i, ps->layer , 1);
		}
		else
		{
			if (a_to_b)
				i = fill_to_a(ps, i, ps->layer, -1);
			else
				i = fill_to_a(ps, i, ps->layer, 1);
		}
		pt++;
	}
	while (pt < ps->n_parts)
	{		
		if (end_b)
		{
			i = fill_to_b(ps, i, ps->layer, -1);
		}
		else
		{
			if (a_to_b)
				i = fill_to_a(ps, i, ps->layer, 1);
			else
				i = fill_to_a(ps, i, ps->layer, -1);
		}
		pt++;
	}
}

static void		put_two_groups(t_ps *ps, int a_to_b, int top_layer, int bot_layer)
{
	t_stack		*from;
	int			len;
	int			i;

	from = (a_to_b) ? ps->a : ps->b;
	len = from->size;
	i = 0;
	while (i < len)
	{
		if (from->head->group == top_layer)
		{
			if (a_to_b)
				do_instruction(ps->a, ps->b, "pb");
			else
				do_instruction(ps->a, ps->b, "pa");
		}
		else if (from->head->group == bot_layer)
		{
			if (a_to_b)
			{
				do_instruction(ps->a, ps->b, "pb");
				do_instruction(ps->a, ps->b, "rb");
			}
			else
			{
				do_instruction(ps->a, ps->b, "pa");
				do_instruction(ps->a, ps->b, "ra");
			}
		}
		else
		{
			if (a_to_b)
				do_instruction(ps->a, ps->b, "ra");
			else
				do_instruction(ps->a, ps->b, "rb");
		}
		i++;
	}
}

static void		radix_sort(t_ps *ps)
{
	int		num_iter;
	int		top;
	int		bot;
	int		in_iter;
	int		out_iter;

	num_iter = log_m_ceil(ps->len, ps->max_symbols);
	out_iter = 1;
	ps->layer = num_iter - 2;
	//////
	// print_stack("Orig", 0, ps->a, ps->b);
	//////

	while (out_iter <= num_iter)
	{
		// if (num_iter % 2)
		// 	update_index(ps, (out_iter % 2));
		// else
		// {
		// 	if (out_iter % 2)
		// 		update_index(ps, (out_iter % 2));
		// 	else
		// 		update_rev_index(ps, (out_iter % 2));
		// }
			
		update_index(ps, (out_iter % 2), (num_iter % 2));
		// top = (ps->max_symbols - 1) / 2 - ((ps->max_symbols % 2) && (out_iter % 2) && (num_iter % 2));
		top = (ps->max_symbols - 1) / 2;
		bot = top + 1;
		in_iter = (ps->max_symbols + 1) / 2;
		while (in_iter > 0)
		{
			// ft_printf("Putting %d, %d\n", top, bot);
			put_two_groups(ps, (out_iter % 2), top, bot);
			top--;
			bot++;
			in_iter--;
		}
		out_iter++;
		ps->sym_p_pt *= ps->max_symbols;

		//////
		print_stack("After outer loop", 0, ps->a, ps->b);
		//////
	}
	if (ps->a->size == 0)
	{
		num_iter = ps->b->size;
		while (num_iter > 0)
		{
			do_instruction(ps->a, ps->b, "pa");
			num_iter--;
		}
	}
	//////
	// print_stack("After sort", 0, ps->a, ps->b);
	//////
}


void			calc_m_and_sort(t_ps *ps)
{
	double 	four_steps;
	double 	five_steps;
	int		n;

	n = ps->a->size;
	ps->len = n;
	four_steps = 2.0 * n * log_m_ceil(n, 4) +  n * (log_m_ceil(n, 4) % 2);
	five_steps = 2.2 * n * log_m_ceil(n, 5) +  n * (log_m_ceil(n, 5) % 2);
	if (four_steps < five_steps)
		ps->max_symbols = 4;
	else
		ps->max_symbols = 5;
	ps->sym_p_pt = 1;

	// /////
	// ps->max_symbols = 4;
	ps->max_symbols = 5;

	ps->n_parts = ps->len / ps->max_symbols + (ps->len % ps->max_symbols != 0);
	// ft_printf("Group Size = %d\n", ps->max_symbols);
	////

	radix_sort(ps);
}
