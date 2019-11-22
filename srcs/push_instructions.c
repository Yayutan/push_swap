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
	if (b->size > 0)
    {
        push(a, pop(b));
		if (a->head)
			a->head->red = 1;
    }
}

void		pb(t_stack *a, t_stack *b)
{
	if (a->size > 0)
    {
        push(b, pop(a));
		if (b->head)
			b->head->red = 1;
    }
}
