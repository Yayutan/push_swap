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

	i_a = (is_a) ? p2 : p1;
	i_b = (is_a) ? p1 : p2;
	while (i_a > 0 || i_b > 0)
	{
		if (i_a > 0 && i_b > 0)
		{
			if (peak(ps->a) < peak(ps->b))
			{
				do_instruction(ps->a, ps->b, "ra");
				i_a--;
			}
			else
			{
				do_instruction(ps->a, ps->b, "pa");
				do_instruction(ps->a, ps->b, "ra");
				i_b--;
			}
		}
		else if (i_a <= 0)
		{
			do_instruction(ps->a, ps->b, "pa");
			do_instruction(ps->a, ps->b, "ra");
			i_b--;
		}
		else if (i_b <= 0)
		{
			do_instruction(ps->a, ps->b, "ra");
			i_a--;
		}
	}
	i_a = p1 + p2;
	while (i_a > 0)
	{
		if (is_a)
			do_instruction(ps->a, ps->b, "rra");
		else
		{
			do_instruction(ps->a, ps->b, "rra");
			do_instruction(ps->a, ps->b, "pb");
		}
		i_a--;
	}
}

void		merge_sort(t_ps *ps, int is_a, int size)
{
	int		mid;
	int		i;
//	if (is_a)
//		print_stack("Looking at a", 0, ps->a, ps->b);
//	else
//		print_stack("Looking at b", 0, ps->a, ps->b);
	if (size == 1)
		return ;
	mid = size / 2;
	i = 0;
	while (i < mid)
	{
		if (is_a)
			do_instruction(ps->a, ps->b, "pb");
		else
			do_instruction(ps->a, ps->b, "pa");
		i++;
	}
	merge_sort(ps, !is_a, mid);
	merge_sort(ps, is_a, size - mid);
	merge(ps, is_a, mid, size - mid);
//	print_stack("After merge", 0, ps->a, ps->b);
}
