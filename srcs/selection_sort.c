/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 21:14:20 by mchuang           #+#    #+#             */
/*   Updated: 2019/12/07 21:14:40 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_int_node	**copy_stack(t_stack *a)
{
	int			i;
	t_int_node	*tmp;
	t_int_node	**list;	

	list = (t_int_node**)ft_memalloc(sizeof(t_int_node*) * a->size);
	i = 0;
	tmp = a->head;
	while (i < a->size)
	{
		list[i] = tmp;
		tmp = tmp->next;
		i++;
	}
	return (list);
}

static int			find_smallest(t_int_node **list, int unsorted, int size)
{
	int		i;
	int		min;
	int		min_i;

	i = unsorted;
	min = list[unsorted]->data;
	min_i = unsorted;
	while (i < size)
	{
		if (list[i]->data < min)
		{
			min = list[i]->data;
			min_i = i;
		}
		i++;
	}
	return (min_i);
}

void				selection_sort(t_stack *a)
{
	t_int_node	**list;
	t_int_node	*tmp;
	int			nxt_sort;
	int			smallest;

	list = copy_stack(a);
	nxt_sort = 0;
	while (nxt_sort < a->size)
	{
		smallest = find_smallest(list, nxt_sort, a->size);
		tmp = list[smallest];
		list[smallest] = list[nxt_sort];
		list[nxt_sort] = tmp;
		list[nxt_sort]->index = nxt_sort;
		nxt_sort++;
	}
	free(list);
}