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

static void			copy_stack(t_ps *ps, t_int_node **sorted)
{
	int			i;
	t_int_node	*tmp;

	i = 0;
	tmp = ps->a->head;
	while (i < ps->a->size)
	{
		sorted[i] = tmp;
		tmp = tmp->next;
		i++;
	}
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

int					selection_sort(t_ps *ps)
{
	t_int_node	*tmp;
	t_int_node	**sorted;
	int			nxt_sort;
	int			smallest;

	sorted = (t_int_node**)ft_memalloc(sizeof(t_int_node*) * ps->len);
	if (!sorted)
		return (0);
	copy_stack(ps, sorted);
	nxt_sort = 0;
	while (nxt_sort < ps->a->size)
	{
		smallest = find_smallest(sorted, nxt_sort, ps->a->size);
		tmp = sorted[smallest];
		sorted[smallest] = sorted[nxt_sort];
		sorted[nxt_sort] = tmp;
		sorted[nxt_sort]->index = nxt_sort;
		nxt_sort++;
	}
	free(sorted);
	return (1);
}
