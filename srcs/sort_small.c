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

static void	sort_three(t_ps *ps)
{
	t_int_node	*cur;

	cur = ps->a->head;
	while (cur && cur->data != ps->sorted[0]->data)
	{
		pt_instruction(ps->a, ps->b, "ra");
		cur = cur->next;
	}
	pt_instruction(ps->a, ps->b, "pb");
	if (ps->a->head->data > ps->a->head->next->data)
		pt_instruction(ps->a, ps->b, "sa");
	pt_instruction(ps->a, ps->b, "pa");
}

static void	sort_four(t_ps *ps)
{
	int			i;
	int			sa;
	int			sb;

	i = 0;
	while (i < 2)
	{
		if (ps->a->head->data == ps->sorted[0]->data || ps->a->head->data == ps->sorted[1]->data)
		{
			pt_instruction(ps->a, ps->b, "pb");
			i++;
		}
		else
			pt_instruction(ps->a, ps->b, "ra");
	}
	sa = ps->a->head->data > ps->a->head->next->data;
	sb = ps->b->head->data < ps->b->head->next->data;
	if (sa && sb)
		pt_instruction(ps->a, ps->b, "ss");
	else if (sa)
		pt_instruction(ps->a, ps->b, "sa");
	else if (sb)
		pt_instruction(ps->a, ps->b, "sb");
	pt_instruction(ps->a, ps->b, "pa");
	pt_instruction(ps->a, ps->b, "pa");
}

static void	sort_five_helper(t_ps *ps)
{
	int			i;

	i = 0;
	while (i < 1)
	{
		if (ps->a->head->data == ps->sorted[2]->data)
		{
			pt_instruction(ps->a, ps->b, "pb");
			i++;
		}
		else
			pt_instruction(ps->a, ps->b, "ra");
	}
	if (ps->a->head->data > ps->a->head->next->data)
		pt_instruction(ps->a, ps->b, "sa");
	pt_instruction(ps->a, ps->b, "pa");
}

static void	sort_five(t_ps *ps)
{
	int			i;
	int			sb;

	i = 0;
	while (i < 2)
	{
		if (ps->a->head->data == ps->sorted[0]->data || ps->a->head->data == ps->sorted[1]->data)
		{
			pt_instruction(ps->a, ps->b, "pb");
			i++;
		}
		else
			pt_instruction(ps->a, ps->b, "ra");
	}
	sb = ps->b->head->data < ps->b->head->next->data;
	if (sb)
		pt_instruction(ps->a, ps->b, "sb");
	sort_five_helper(ps);
	pt_instruction(ps->a, ps->b, "pa");
	pt_instruction(ps->a, ps->b, "pa");
}

void		sort_small(t_ps *ps)
{
	if (ps->len == 2)
		pt_instruction(ps->a, ps->b, "sa");
	else if (ps->len == 3)
		sort_three(ps);
	else if (ps->len == 4)
		sort_four(ps);
	else if (ps->len == 5)
		sort_five(ps);
}