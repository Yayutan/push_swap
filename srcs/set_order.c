/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_order.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 09:18:44 by mchuang           #+#    #+#             */
/*   Updated: 2020/02/10 09:18:45 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		get_gp_4(char *layer, int gp_size, int index)
{
	char		cur_ord;
	int			gp;

	cur_ord = layer[index / gp_size];
	gp = (index / (gp_size / 4)) % 4;
	if (cur_ord == '0')
		gp = 3 - gp;
	return (gp);
}

static int		get_gp_5(char *layer, int gp_size, int last, int index)
{
	char		cur_ord;
	int			gp;

	cur_ord = layer[index / gp_size];
	gp = (index / (gp_size / 5)) % 5;
	if (last)
		return (gp + 1);
	if (cur_ord == '0')
		gp = 4 - gp;
	return (gp);
}

void			set_gp_stack(t_ps *ps, int to_b, int ly, int last)
{
	t_int_node	*cur;
	int			in;

	cur = (ps->a->size) ? ps->a->head : ps->b->head;
	while (cur)
	{
		in = (to_b) ? (ps->len - 1 - cur->index) : cur->index;
		if (ps->max_symbols == 5)
			cur->group = get_gp_5(ps->order[0], ps->sym_p_pt * 5, last, in);
		else
		{
			if (!last)
				cur->group = get_gp_4(ps->order[0], ps->sym_p_pt * 4, in);
			else
				cur->group = get_gp_4(ps->order[ly - 1], ps->sym_p_pt * 4, in);
		}
		cur = cur->next;
	}
}

void			set_order_5(char **order, int layers)
{
	int			i;
	int			j;
	int			num_elements;

	order[layers - 1] = ft_strdup((layers % 2) ? "00111" : "11000");
	i = layers - 1;
	num_elements = 25;
	while (--i >= 0)
	{
		order[i] = ft_strnew(num_elements);
		j = -5;
		while ((j += 5) < num_elements)
		{
			if (i % 2 == 0)
				(order[i + 1][j / 5] == '0') ?
				ft_strncpy((*(order + i) + j), "00011", 5) :
				ft_strncpy((*(order + i) + j), "00111", 5);
			else
				(order[i + 1][j / 5] == '0') ?
				ft_strncpy((*(order + i) + j), "11000", 5) :
				ft_strncpy((*(order + i) + j), "11100", 5);
		}
		num_elements *= 5;
	}
}

void			set_order_4(char **order, int layers)
{
	int			i;
	int			j;
	int			num_elements;

	order[layers - 1] = ft_strdup("1100");
	i = layers - 2;
	num_elements = 16;
	while (i >= 0)
	{
		order[i] = ft_strnew(num_elements);
		j = 0;
		while ((j < num_elements))
		{
			ft_strncpy((*(order + i) + j), "0011", 4);
			j += 4;
		}
		i--;
		num_elements *= 4;
	}
}
