/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 20:30:24 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/24 20:30:41 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		merge(t_ps *ps, int is_a, int p1, int p2)
{
	int		i_a;
	int		i_b;

//	i_1 = p1;
//	i_1 = p1;
	while (i > 0)
	{
		if ()
		i--;
	}
}

void		merge_sort(t_ps *ps, int is_a, int size)
{
	int		mid;
	int		i;

	if (is_a)
		print_stack("Looking at a", 0, ps->a, NULL);
	else
		print_stack("Looking at b", 0, NULL, ps->b);
	if (size == 1)
		return ;
	mid = size / 2;
	i = 0;
	while (i < mid)
	{
		if (is_a)
			do_instruction(ps->a, ps->b, "pb")
		else
			do_instruction(ps->a, ps->b, "pa")
		i++;
	}
	merge_sort(ps, !is_a, mid);
	merge_sort(ps, is_a, size - mid);
	merge(ps, is_a, mid, size - mid);
}
