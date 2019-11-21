/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_rotate_instructions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:19:52 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/20 21:19:54 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"

void		rra(t_stack *a, t_stack *b)
{
	t_int_node	*cur;
    t_int_node	*pre;

	if (a->size > 1)
	{
		cur = a->head;
		pre = NULL;
		while (cur->next)
		{
			pre = cur;
			cur = cur->next;            
		}
		pre->next = NULL;
		cur->next = a->head;
		a->head = cur;
	}
	cur = b->head;
}

void		rrb(t_stack *a, t_stack *b)
{
	t_int_node	*cur;
    t_int_node	*pre;

	if (b->size > 1)
	{
		cur = b->head;
		pre = NULL;
		while (cur->next)
		{
			pre = cur;
			cur = cur->next;            
		}
		pre->next = NULL;
		cur->next = b->head;
		b->head = cur;
	}
	cur = a->head;
}

void		rrr(t_stack *a, t_stack *b)
{
	rra(a, b);
	rrb(a, b);
}
