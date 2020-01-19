/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 20:50:18 by mchuang           #+#    #+#             */
/*   Updated: 2020/01/09 20:50:20 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_by_index(t_ps *ps, int i)
{
	t_int_node	*cur;
	int			ret;

	ret = 0;
	cur = ps->a->head;
	while (cur)
	{
		if (cur->data == ps->sorted[i]->data)
			break ;
		ret++;
		cur = cur->next;
	}
	return (ret);
}

static void	sort_three(t_ps *ps, int st)
{
	int			i;

	i = find_by_index(ps, st);
	if (i == 0)
	{
		ex_and_store_instructions(ps, "pb");
		ex_and_store_instructions(ps, "sa");
		ex_and_store_instructions(ps, "pa");
	}
	else if (i == 1)
	{
		if (ps->a->head->data == ps->sorted[st + 1]->data)
		{
			ex_and_store_instructions(ps, "rra");
			ex_and_store_instructions(ps, "sa");
			ex_and_store_instructions(ps, "rra");
		}
		else
			ex_and_store_instructions(ps, "ra");
	}
	else
	{
		if (ps->a->head->data > ps->a->head->next->data)
			ex_and_store_instructions(ps, "sa");
		ex_and_store_instructions(ps, "rra");
	}
}

static void	sort_four(t_ps *ps)
{
	int			i;
	int			s[2];

	i = 0;
	while (i < 2)
	{
		if (ps->a->head->data == ps->sorted[0]->data ||
			ps->a->head->data == ps->sorted[1]->data)
		{
			ex_and_store_instructions(ps, "pb");
			i++;
		}
		else
			ex_and_store_instructions(ps, "ra");
	}
	s[0] = ps->a->head->data > ps->a->head->next->data;
	s[1] = ps->b->head->data < ps->b->head->next->data;
	if (s[0])
		ex_and_store_instructions(ps, "sa");
	if (s[1])
		ex_and_store_instructions(ps, "sb");
	ex_and_store_instructions(ps, "pa");
	ex_and_store_instructions(ps, "pa");
}

static void	sort_five(t_ps *ps)
{
	int			i;
	int			sb;

	i = 0;
	while (i < 2)
	{
		if (ps->a->head->data == ps->sorted[0]->data ||
			ps->a->head->data == ps->sorted[1]->data)
		{
			ex_and_store_instructions(ps, "pb");
			i++;
		}
		else
			ex_and_store_instructions(ps, "ra");
	}
	sb = ps->b->head->data < ps->b->head->next->data;
	if (sb)
		ex_and_store_instructions(ps, "sb");
	if (!check_sorted(ps->a))
		sort_three(ps, 2);
	ex_and_store_instructions(ps, "pa");
	ex_and_store_instructions(ps, "pa");
}

void		sort_small(t_ps *ps)
{
	if (ps->len == 2)
		ex_and_store_instructions(ps, "sa");
	else if (ps->len == 3)
		sort_three(ps, 0);
	else if (ps->len == 4)
		sort_four(ps);
	else if (ps->len == 5)
		sort_five(ps);
}
