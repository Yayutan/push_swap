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
		ft_err_exit("Failed to alllocate checker struct");
	if (!(to_ret->a = st_init()))
	{
		free(to_ret);
		ft_err_exit("Failed to alllocate stack A");
	}
	if (!(to_ret->b = st_init()))
	{
		free_stack(to_ret->a);
		free(to_ret);
		ft_err_exit("Failed to alllocate stack B");
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
	if (ps->sorted)
		free(ps->sorted);
	free(ps);
}

static int			add_string_n(t_ps *ps, char **n)
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

t_stack		*check_num(t_ps *ps, int n_c, char **n_v)
{
	int		i;
	char	**n;

	i = n_c - 1;
	while (i >= 0)
	{
		n = ft_strsplit(n_v[i], ' ');
		if (!n)
			return (NULL);
		if (!*n || !(add_string_n(ps, n)))
		{
			clean_str_arr(n);
			return (NULL);
		}
		clean_str_arr(n);
		i--;
	}
	return (ps->a);
}

int		check_sorted(t_stack *st)
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
