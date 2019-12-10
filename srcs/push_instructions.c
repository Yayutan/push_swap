/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:15:28 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/20 21:15:31 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"

void		pa(t_stack *a, t_stack *b)
{
	t_int_node		*tmp;

	if (b->size > 0)
	{
		tmp = b->head;
		b->head = b->head->next;
		tmp->next = a->head;
		a->head = tmp;
		a->head->red = 1;
		b->size--;
		a->size++;
	}
}

void		pb(t_stack *a, t_stack *b)
{
	t_int_node		*tmp;

	if (a->size > 0)
	{
		tmp = a->head;
		a->head = a->head->next;
		tmp->next = b->head;
		b->head = tmp;
		b->head->red = 1;
		a->size--;
		b->size++;
	}
}
