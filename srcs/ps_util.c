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

static void		update_index(t_ps *ps, int a_to_b)
{
	t_int_node	*cur;
	int			index;
	int			base;
	int			len;
	int			num_groups;

	cur = (a_to_b) ? ps->a->head : ps->b->head;
	base = ps->base;
	len = (a_to_b) ? ps->a->size : ps->b->size;
	num_groups = len / (base * ps->n_group);
	// while (cur)
	while (len >= base * 2 && cur)
	{
		index = cur->index;
		if ((index / (base * ps->n_group)) <= (num_groups / 2))
			cur->group = ((ps->n_group - 1) - ((index / base) % ps->n_group));
		else
			cur->group = ((index / base) % ps->n_group);
		///
		ft_printf("i:%d, base:%d, len:%d, res:%d\n", cur->index, base, len, cur->group);
		///
		cur = cur->next;
	}
	while (len < base * 2 && cur)
	{
		index = cur->index;
		if (index < base)
			cur->group = 0;
		else
			cur->group = (ps->n_group - 1);
		///
		ft_printf("i:%d, base:%d, len:%d, res:%d\n", cur->index, base, len, cur->group);
		///
		cur = cur->next;
	}
}

static void		update_index_reverse(t_ps *ps, int a_to_b)
{
	t_int_node	*cur;
	int			index;
	int			base;
	int			len;
	int			num_groups;

	cur = (a_to_b) ? ps->a->head : ps->b->head;
	base = ps->base;
	len = (a_to_b) ? ps->a->size : ps->b->size;
	num_groups = len / (base * ps->n_group);
	while (len >= base * 2 && cur)
	{
		index = cur->index;
		if ((index / (base * ps->n_group)) > (num_groups / 2))
			cur->group = ((ps->n_group - 1) - ((index / base) % ps->n_group));
		else
			cur->group = ((index / base) % ps->n_group);
		///
		ft_printf("i:%d, base:%d, len:%d, res:%d\n", cur->index, base, len, cur->group);
		///
		cur = cur->next;
	}
	while (len < base * 2 && cur)
	{
		index = cur->index;
		if (index < base)
			cur->group = 0;
		else
			cur->group = (ps->n_group - 1);
		///
		ft_printf("i:%d, base:%d, len:%d, res:%d\n", cur->index, base, len, cur->group);
		///
		cur = cur->next;
	}
}

// static void		update_index_order(t_ps *ps) // a to b
// {
// 	t_int_node	*cur;
// 	int			index;
// 	int			base;
// 	int			len;
// 	int			num_groups;

// 	cur = ps->a->head;
// 	base = ps->base;
// 	len = ps->a->size;
// 	num_groups = len / (base * ps->n_group);
// 	while (cur)
// 	{
// 		index = cur->index;
// 		if ((index / (base * ps->n_group)) <= (num_groups / 2))
// 			cur->group = ((ps->n_group - 1) - ((index / base) % ps->n_group));
// 		else
// 			cur->group = ((index / base) % ps->n_group);
// 		///
// 		// ft_printf("i:%d, base:%d, len:%d, res:%d\n", cur->index, base, len, cur->group);
// 		///
// 		cur = cur->next;
// 	}
// }

static void		put_two_groups(t_ps *ps, int a_to_b, int top_layer, int bot_layer)
{
	t_stack		*from;
	int			len;
	int			m;
	int			i;

	// /////
	// ft_printf("Putting %d and %d:\n", top_layer, bot_layer);
	// ////

	m = ps->n_group;
	from = (a_to_b) ? ps->a : ps->b;
	len = from->size;
	i = 0;
	while (i < len)
	{
		/////
		// ft_printf("Looking at %d (%d)\n", from->head->data, from->head->group);
		////

		if (from->head->group == top_layer)
		// if (from->head->index % m == top_layer)
		{
			// from->head->index /= m;

			// /////
			// ft_printf("Modified index to (%d)\n", from->head->index);
			// ////

			if (a_to_b)
				do_instruction(ps->a, ps->b, "pb");
			else
				do_instruction(ps->a, ps->b, "pa");
		}
		else if (from->head->group == bot_layer)
		// else if (from->head->index % m == bot_layer)
		{
			// from->head->index /= m;

			// /////
			// ft_printf("Modified index to (%d)\n", from->head->index);
			// ////

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

	num_iter = log_m_ceil(ps->a->size, ps->n_group);
	out_iter = 1;
	while (out_iter <= num_iter)
	{
		//////
		print_stack("After outer loop", 0, ps->a, ps->b);
		//////

		// update_index_reverse_order(ps, (out_iter % 2));
		// update_index(ps, (out_iter % 2));
		if (out_iter % 2)
			update_index(ps, (out_iter % 2));
		else
			update_index_reverse(ps, (out_iter % 2));

		// top = (out_iter % 2) ? ps->n_group / 2 : (ps->n_group - 1) / 2;
		// bot = (out_iter % 2) ? top - 1 : top + 1;
		top = (ps->n_group - 1) / 2;
		bot = top + 1;
		in_iter = (ps->n_group + 1) / 2;
		while (in_iter > 0) // inner loop
		{
			put_two_groups(ps, (out_iter % 2), top, bot);

			// ////////
			// print_stack("After putting two groups", 0, ps->a, ps->b);
			// ////////

			// top += (out_iter % 2) ? 1 : -1;
			// bot += (out_iter % 2) ? -1 : 1;
			top--;
			bot++;
			in_iter--;
		}
		out_iter++;
		ps->base *= ps->n_group;
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
}


void			calc_m_and_sort(t_ps *ps)
{
	double 	four_steps;
	double 	five_steps;
	int		n;

	n = ps->a->size;
	four_steps = 2.0 * n * log_m_ceil(n, 4) +  n * (log_m_ceil(n, 4) % 2);
	five_steps = 2.2 * n * log_m_ceil(n, 5) +  n * (log_m_ceil(n, 5) % 2);
	if (four_steps < five_steps)
		ps->n_group = 4;
	else
		ps->n_group = 5;
	ps->base = 1;

	/////
	ft_printf("Group Size = %d\n", ps->n_group);
	////

	radix_sort(ps);
}
