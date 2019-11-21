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
