/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:15:19 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/20 21:15:21 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"

void		sa(t_stack *a, t_stack *b)
{
	int         tmp;
    t_int_node  *cur;

    if (a->size >= 2)
    {
        cur = a->head;
        tmp = cur->data;
        cur->data = cur->next->data;
        cur->next->data = tmp;
		cur->red = 1;
		cur->next->red = 1;
    }
	cur = b->head;
}

void		sb(t_stack *a, t_stack *b)
{
	int         tmp;
    t_int_node  *cur;

    if (b->size >= 2)
    {
        cur = b->head;
        tmp = cur->data;
        cur->data = cur->next->data;
        cur->next->data = tmp;
		cur->red = 1;
		cur->next->red = 1;
    }
	cur = a->head;
}

void		ss(t_stack *a, t_stack *b)
{
	sa(a, b);
	sb(a, b);
}
