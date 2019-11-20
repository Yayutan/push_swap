/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 21:52:42 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/19 21:52:53 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"


//ft_printf("%*s%d%*s%d%*s\n", 5, " ", num_a, 10, " ", num_b, 15, " ")
void			print_stack(t_stack *st_a, t_stack *st_b)
{
	t_int_node	*cur_a;
	t_int_node	*cur_b;

	cur_a = (st_a) ? st_a->head : NULL;
	cur_b = (st_b) ? st_b->head : NULL;
	while (cur_a || cur_b)
	{
		(cur_a) ? ft_putnbr(cur_a->data) : ft_putchar(' ');
		ft_putchar(' ');
		(cur_b) ? ft_putnbr(cur_b->data) : ft_putchar(' ');
		ft_putchar('\n');
		cur_a = (cur_a) ? cur_a->next : cur_a;
		cur_b = (cur_b) ? cur_b->next : cur_b;
	}
	ft_putendl("- -");
	ft_putendl("a b");
}

void			print_queue(char *name, t_queue *q)
{
	t_str_node	*cur;

	ft_putendl(name);
	if (!q)
		return ;
	cur = q->head;
	while (cur)
	{
		ft_putendl(cur->data);
		cur = cur->next;
	}
}

void			clean_up_structs(t_stack *a, t_stack *b, t_queue *ins)
{
	free_stack(a);
	free_stack(b);
	free_queue(ins);
}

void			setup_structs(t_stack **a, t_stack **b, t_queue **ins)
{
	if (!(*a = st_init()))
		ft_err_exit("Failed to alllocate stack A");
	if (!(*b = st_init()))
	{
		free_stack(*a);
		ft_err_exit("Failed to alllocate stack B");
	}
	if (!(*ins = q_init()))
	{
		free_stack(*a);
		free_stack(*b);
		ft_err_exit("Failed to alllocate instruction Q");
	}	
}
