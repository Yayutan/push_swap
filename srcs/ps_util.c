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

t_ps			*setup_structs(void)
{
	t_ps	*to_ret;

	if (!(to_ret = ft_memalloc(sizeof(t_ps))))
		ft_err_exit("Failed to alllocate ps struct");
	to_ret->a = st_init();
	to_ret->b = st_init();
	to_ret->ins = q_init();
	if (!to_ret->a || !to_ret->b || !to_ret->ins)
	{
		if (to_ret->a)
			free_stack(to_ret->a);
		if (to_ret->b)
			free_stack(to_ret->b);
		if (to_ret->ins)
			free_queue(to_ret->ins);
		free(to_ret);
		ft_err_exit("Failed to alllocate stack and Q");
	}
	to_ret->sorted = NULL;
	to_ret->n_parts = 0;
	to_ret->sym_p_pt = 1;
	to_ret->layer = 0;
	to_ret->len = 0;
	to_ret->max_symbols = 0;
	return (to_ret);
}

void			clean_up_structs(t_ps *ps)
{
	free_stack(ps->a);
	free_stack(ps->b);
	free_queue(ps->ins);
	if (ps->sorted)
		free(ps->sorted);
	free(ps);
}

int				check_sorted(t_stack *st)
{
	t_int_node	*cur;

	cur = st->head;
	while (cur->next)
	{
		if (cur->data > cur->next->data)
			return (0);
		cur = cur->next;
	}
	return (1);
}

int				exponential(int b, int p)
{
	int		i;
	int		res;

	i = 0;
	res = 1;
	while (i < p)
	{
		res *= b;
		i++;
	}
	return (res);
}

int				log_m_ceil(int n, int m)
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
