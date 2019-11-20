/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:50:25 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/19 16:50:27 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

t_int_node			*st_new_element(int n)
{
	t_int_node	*to_ret;

	to_ret = ft_memalloc(sizeof(t_int_node*));
	to_ret->data = n;
	to_ret->next = NULL;
	return (to_ret);
}

t_stack				*push(t_stack *st, t_int_node *p)
{
	if (!st || !p)
		return (st);
	if (!(st->head))
	{
		st->head = p;
		st->size = 1;
	}
	else
	{
		p->next = st->head;
		st->head = p;
		(st->size)++;	
	}
	return (st);
}

int					pop(t_stack *st)
{
	int		to_ret;

	if (!st || !(st->head))
		return (-42);
	to_ret = st->head->data;
	st->head = st->head->next;
	(st->size)--;
	return (to_ret);
}

int					peak(t_stack *st)
{
	if (!st || !(st->head))
		return (-42);
	return (st->head->data);
}

int					st_len(t_stack *st)
{
	t_int_node	*cur;
	int			len;

	if (!st)
		return (0);
	len = 0;
	cur = st->head;
	while (cur)
	{
		len++;
		cur = cur->next;
	}
	return (len);
}
