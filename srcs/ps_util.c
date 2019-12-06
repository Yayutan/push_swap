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

//void	five_case(t0_ps *ps)
//{
//	// assuming there is only 1 2 3 4 5
//	  
//}


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
                ps->n_ins++;
				i_a--;
			}
			else
			{
				do_instruction(ps->a, ps->b, "pa");
				do_instruction(ps->a, ps->b, "ra");
                ps->n_ins += 2;
				i_b--;
			}
		}
		else if (i_a <= 0)
		{
			do_instruction(ps->a, ps->b, "pa");
			do_instruction(ps->a, ps->b, "ra");
            ps->n_ins += 2;
			i_b--;
		}
		else if (i_b <= 0)
		{
			do_instruction(ps->a, ps->b, "ra");
            ps->n_ins++;
			i_a--;
		}
	}
	i_a = p1 + p2;
	while (i_a > 0)
	{
		if (is_a)
        {
            do_instruction(ps->a, ps->b, "rra");
            ps->n_ins++;
        }
		else
		{
			do_instruction(ps->a, ps->b, "rra");
			do_instruction(ps->a, ps->b, "pb");
            ps->n_ins += 2;
		}
		i_a--;
	}
}

void		merge_sort(t_ps *ps, int is_a, int size)
{
	int		mid;
	int		i;
	if (size == 1)
		return ;
    else if (size == 2)
    {
        if (is_a && ps->a->head->data > ps->a->head->next->data)
            do_instruction(ps->a, ps->b, "sa");
        else if (!is_a && ps->b->head->data > ps->b->head->next->data)
            do_instruction(ps->a, ps->b, "sb");
        ps->n_ins++;
        return ;
    }
	// add another base case: if sorted, do nothing
	mid = size / 2;
	i = 0;
	while (i < mid)
	{
		if (is_a)
			do_instruction(ps->a, ps->b, "pb");
		else
			do_instruction(ps->a, ps->b, "pa");
		i++;
        ps->n_ins++;
	}
	merge_sort(ps, !is_a, mid);
	merge_sort(ps, is_a, size - mid);
	merge(ps, is_a, mid, size - mid);
}

int				add_string_n(t_ps *ps, char **n)
{
	int		i;
	int		*nxt;

	i = 0;
	while (n[i + 1])
		i++;
	while (i >= 0)
	{
		nxt = NULL;
		if (!(nxt = valid_int(n[i])) || !(push(ps->a, *nxt)))
		{
			if (nxt)
				free(nxt);
			return (0);
		}
		if (nxt)
			free(nxt);
		i--;
	}
	return (1);
}