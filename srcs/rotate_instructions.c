/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_instructions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:15:40 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/20 21:15:42 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"

void	ra(t_stack *a, t_stack *b)
{
	t_int_node	*cur;
	t_int_node	*tail;

	if (a->size > 1)
	{
		cur = a->head;
		tail = a->head;
		tail->red = 1;
		while (cur->next)
			cur = cur->next;
		a->head = a->head->next;
		cur->next = tail;
		tail->next = NULL;
	}
	cur = b->head;
}

void	rb(t_stack *a, t_stack *b)
{
	t_int_node	*cur;
	t_int_node	*tail;

	if (b->size > 1)
	{
		cur = b->head;
		tail = b->head;
		tail->red = 1;
		while (cur->next)
			cur = cur->next;
		b->head = b->head->next;
		cur->next = tail;
		tail->next = NULL;
	}
	cur = a->head;
}

void	rr(t_stack *a, t_stack *b)
{
	ra(a, b);
	rb(a, b);
}
