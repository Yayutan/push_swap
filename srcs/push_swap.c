/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:21:33 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/18 19:21:35 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

static t_stack		*check_num(t_ps *ps, int n_c, char **n_v)
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

int					main(int ac, char **av)
{
	t_ps	*ps;

	ps = setup_structs();
	if (!check_num(ps, ac - 1, av + 1))
	{
		clean_up_structs(ps);
		ft_err_exit("Error");
	}
	ps->len = ps->a->size;
	if (ps->len > 1 && !check_sorted(ps->a))
	{
		if (!selection_sort(ps))
		{
			clean_up_structs(ps);
			ft_err_exit("Error");
		}
		(ps->len <= 5) ? sort_small(ps) : radix_sort(ps);
	}
	clean_up_structs(ps);
	return (0);
}
