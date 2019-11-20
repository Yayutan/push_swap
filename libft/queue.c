/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:50:30 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/19 16:50:34 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

t_str_node			*q_new_element(char *n)
{
	t_str_node	*to_ret;

	to_ret = ft_memalloc(sizeof(t_str_node*));
	to_ret->data = n;
	to_ret->next = NULL;
	return (to_ret);
}

t_queue				*enqueue(t_queue *q, t_str_node *p)
{
	if (!q || !p)
		return (q);
	if (!(q->head))
	{
		q->head = p;
		q->tail = p;
		q->size = 1;
	}
	else
	{
		q->tail->next = p;
		q->tail = p;
		(q->size)++;	
	}
	return (q);
}

char				*dequeue(t_queue *q)
{
	char	*to_ret;

	if (!q || !(q->head))
		return ("-42");
	to_ret = q->head->data;
	q->head = q->head->next;
	(q->size)--;
	return (to_ret);
}

char				*front(t_queue *q)
{
	if (!q || !(q->head))
		return ("-42");
	return (q->head->data);
}

int					q_len(t_queue *q)
{
	t_str_node	*cur;
	int			len;

	if (!q)
		return (0);
	len = 0;
	cur = q->head;
	while (cur)
	{
		len++;
		cur = cur->next;
	}
	return (len);
}
