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

static int		log_m_ceil(int n, int m)
{
	int		log;
	int		cur;

	log = 0;
	cur = 1;
	while (cur < n)
	{
		cur *= m;
		log++;
	}
	return (log);
}

static void		put_two_groups(t_ps *ps, int a_to_b, int top_layer, int bot_layer)
{
	t_stack		*from;
	int			num_left;
	int			m;

	// /////
	// ft_printf("Putting %d and %d:\n", top_layer, bot_layer);
	// ////

	m = ps->n_group;
	from = (a_to_b) ? ps->a : ps->b;
	num_left = from->size;
	while (num_left > 0)
	{

		// /////
		// ft_printf("Looking at %d (%d)\n", from->head->data, from->head->index);
		// ////

		if (from->head->index % m == top_layer)
		{
			from->head->index /= m;

			// /////
			// ft_printf("Modified index to (%d)\n", from->head->index);
			// ////

			if (a_to_b)
				do_instruction(ps->a, ps->b, "pb");
			else
				do_instruction(ps->a, ps->b, "pa");
		}
		else if (from->head->index % m == bot_layer)
		{
			from->head->index /= m;

			// /////
			// ft_printf("Modified index to (%d)\n", from->head->index);
			// ////

			if (a_to_b)
			{
				do_instruction(ps->a, ps->b, "pb");
				do_instruction(ps->a, ps->b, "rb");
			}
			else
			{
				do_instruction(ps->a, ps->b, "pa");
				do_instruction(ps->a, ps->b, "ra");
			}
		}
		else
		{
			if (a_to_b)
				do_instruction(ps->a, ps->b, "ra");
			else
				do_instruction(ps->a, ps->b, "rb");
		}
		num_left--;
	}
}

static void		radix_sort(t_ps *ps)
{
	int		num_iter;
	int		top;
	int		bot;
	int		in_iter;
	int		out_iter;

	num_iter = log_m_ceil(ps->a->size, ps->n_group);
	out_iter = 1;
	while (out_iter <= num_iter)
	{
		////////
		// print_stack("After 1 outer loops", 0, ps->a, ps->b);
		////////
		
		top = (out_iter % 2) ? ps->n_group / 2 : (ps->n_group - 1) / 2;
		bot = (out_iter % 2) ? top - 1 : top + 1;
		in_iter = (ps->n_group + 1) / 2;
		while (in_iter > 0) // inner loop
		{
			put_two_groups(ps, (out_iter % 2), top, bot);

			// ////////
			// print_stack("After putting two groups", 0, ps->a, ps->b);
			// ////////

			top += (out_iter % 2) ? 1 : -1;
			bot += (out_iter % 2) ? -1 : 1;
			in_iter--;
		}
		out_iter++;
	}
	if (ps->a->size == 0)
	{
		num_iter = ps->b->size;
		while (num_iter > 0)
		{
			do_instruction(ps->a, ps->b, "pa");
			num_iter--;
		}
	}
}


void			calc_m_and_sort(t_ps *ps)
{
	double 	four_steps;
	double 	five_steps;
	int		n;

	n = ps->a->size;
	four_steps = 2.0 * n * log_m_ceil(n, 4) +  n * (log_m_ceil(n, 4) % 2);
	five_steps = 2.2 * n * log_m_ceil(n, 5) +  n * (log_m_ceil(n, 5) % 2);
	if (four_steps < five_steps)
		ps->n_group = 4;
	else
		ps->n_group = 5;

	/////
	// ft_printf("Group Size = %d\n", ps->n_group);
	////
	radix_sort(ps);
}



//static void		merge_in_p(t_ps *ps, int is_a, int p1, int p2)
//{
//	int		i_a;
//	int		i_b;
//    int     i;
//
//	i_a = (is_a) ? p2 : p1;
//	i_b = (is_a) ? p1 : p2;
//    i = (is_a) ? i_b : i_a;
//    while (i > 0)
//    {
//        if (is_a)
//			do_instruction(ps->a, ps->b, "rb");
//        else
//			do_instruction(ps->a, ps->b, "ra");
//		i--;
//    }
//    while (i_a > 0 || i_b > 0)
//	{
//		if (is_a)
//		{
//			// put everything in order in A
//		}
//		else
//		{
//			// put everything in reverse order in B
//		}
//		
//		
//		
//		
//		if (i_a > 0 && i_b > 0)
//		{
//			if (peak(ps->a) < peak(ps->b))
//			{
//				do_instruction(ps->a, ps->b, "ra");
//				i_a--;
//			}
//			else
//			{
//				do_instruction(ps->a, ps->b, "pa");
//				do_instruction(ps->a, ps->b, "ra");
//				i_b--;
//			}
//		}
//		else if (i_a <= 0)
//		{
//			do_instruction(ps->a, ps->b, "pa");
//			do_instruction(ps->a, ps->b, "ra");
//			i_b--;
//		}
//		else if (i_b <= 0)
//		{
//			do_instruction(ps->a, ps->b, "ra");
//			i_a--;
//		}
//	}
//}

// static void		merge(t_ps *ps, int is_a, int p1, int p2)
// {
// 	int		i_a;
// 	int		i_b;

// 	i_a = (is_a) ? p2 : p1;
// 	i_b = (is_a) ? p1 : p2;
// 	while (i_a > 0 || i_b > 0)
// 	{
// 		if (i_a > 0 && i_b > 0)
// 		{
// 			if (peak(ps->a) < peak(ps->b))
// 			{
// 				do_instruction(ps->a, ps->b, "ra");
//                 ps->n_ins++;
// 				i_a--;
// 			}
// 			else
// 			{
// 				do_instruction(ps->a, ps->b, "pa");
// 				do_instruction(ps->a, ps->b, "ra");
//                 ps->n_ins += 2;
// 				i_b--;
// 			}
// 		}
// 		else if (i_a <= 0)
// 		{
// 			do_instruction(ps->a, ps->b, "pa");
// 			do_instruction(ps->a, ps->b, "ra");
//             ps->n_ins += 2;
// 			i_b--;
// 		}
// 		else if (i_b <= 0)
// 		{
// 			do_instruction(ps->a, ps->b, "ra");
//             ps->n_ins++;
// 			i_a--;
// 		}
// 	}
// 	i_a = p1 + p2;
// 	while (i_a > 0)
// 	{
// 		if (is_a)
//         {
//             do_instruction(ps->a, ps->b, "rra");
//             ps->n_ins++;
//         }
// 		else
// 		{
// 			do_instruction(ps->a, ps->b, "rra");
// 			do_instruction(ps->a, ps->b, "pb");
//             ps->n_ins += 2;
// 		}
// 		i_a--;
// 	}
// }

// void		merge_sort(t_ps *ps, int is_a, int size)
// {
// 	int		mid;
// 	int		i;
// 	if (size == 1)
// 		return ;
//     else if (size == 2)
//     {
//         if (is_a && ps->a->head->data > ps->a->head->next->data)
//             do_instruction(ps->a, ps->b, "sa");
//         else if (!is_a && ps->b->head->data > ps->b->head->next->data)
//             do_instruction(ps->a, ps->b, "sb");
//         ps->n_ins++;
//         return ;
//     }
// 	// add another base case: if sorted, do nothing
// 	mid = size / 2;
// 	i = 0;
// 	while (i < mid)
// 	{
// 		if (is_a)
// 			do_instruction(ps->a, ps->b, "pb");
// 		else
// 			do_instruction(ps->a, ps->b, "pa");
// 		i++;
//         ps->n_ins++;
// 	}
// 	merge_sort(ps, !is_a, mid);
// 	merge_sort(ps, is_a, size - mid);
// 	merge(ps, is_a, mid, size - mid);
// }
