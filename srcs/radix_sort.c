/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 03:32:06 by mchuang           #+#    #+#             */
/*   Updated: 2020/01/11 03:32:10 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			ex_and_store_instructions(t_ps *ps, char *ins)
{
	ex_instruction(ps->a, ps->b, ins);
	enqueue(ps->ins, ins);
}

static void		put_two_groups(t_ps *ps, int a_to_b, int top, int bot)
{
	t_stack		*from;
	char		ins[3];
	int			i;

	from = (a_to_b) ? ps->a : ps->b;
	i = from->size;
	while (--i >= 0)
	{
		if (from->head->group == bot)
		{
			(a_to_b) ? ft_strcpy(ins, "pb") : ft_strcpy(ins, "pa");
			ex_and_store_instructions(ps, ins);
			(a_to_b) ? ft_strcpy(ins, "rb") : ft_strcpy(ins, "ra");
			ex_and_store_instructions(ps, ins);
		}
		else
		{
			if (from->head->group == top)
				(a_to_b) ? ft_strcpy(ins, "pb") : ft_strcpy(ins, "pa");
			else
				(a_to_b) ? ft_strcpy(ins, "ra") : ft_strcpy(ins, "rb");
			ex_and_store_instructions(ps, ins);
		}
	}
}

static void		put_by_index(t_ps *ps, int a_to_b)
{
	int		top;
	int		bot;
	int		iter;

	top = (ps->max_symbols - 1) / 2;
	bot = top + 1;
	iter = (ps->max_symbols + 1) / 2;
	while (iter > 0)
	{
		put_two_groups(ps, a_to_b, top, bot);
		top--;
		bot++;
		iter--;
	}
}

static void		sort(t_ps *ps)
{
	int		num_iter;
	int		out_iter;

	num_iter = log_m_ceil(ps->len, ps->max_symbols);
	ps->order = (char**)ft_memalloc((num_iter + 1) * sizeof(char*));
	ps->order[num_iter] = NULL;
	if (ps->max_symbols == 4)
		set_order_4(ps->order, num_iter);
	else
		set_order_5(ps->order, num_iter);
	out_iter = 1;
	while (out_iter <= num_iter)
	{
		set_gp_stack(ps, (num_iter % 2), num_iter, (out_iter == num_iter));
		put_by_index(ps, (out_iter % 2));
		out_iter++;
		ps->sym_p_pt *= ps->max_symbols;
	}
	if (ps->b->size != 0)
	{
		while (ps->b->head)
			ex_and_store_instructions(ps, "pa");
	}
}

void			radix_sort(t_ps *ps)
{
	double		four_steps;
	double		five_steps;
	int			n;

	n = ps->len;
	four_steps = 2.0 * n * log_m_ceil(n, 4) + n * (log_m_ceil(n, 4) % 2);
	five_steps = 2.2 * n * log_m_ceil(n, 5) + n * (log_m_ceil(n, 5) % 2);
	ps->max_symbols = (four_steps < five_steps) ? 4 : 5;
	sort(ps);
}
