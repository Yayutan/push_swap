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

static void			clean_up_structs(t_ps *ps)
{
	free_stack(ps->a);
	free_stack(ps->b);
	free(ps);
}

static t_ps			*setup_structs(void)
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
    to_ret->n_ins = 0;
	return (to_ret);
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

int		main(int ac, char **av)
{
	t_ps	*ps;

	ps = setup_structs();
	if (!check_num(ps, ac - 1, av + 1))
	{
		clean_up_structs(ps);
		ft_err_exit("Error");
	}
//	print_stack("B4 Sort", 0, ps->a, ps->b);
	if (ps->a->size > 0)
	{
		merge_sort(ps, 1, ps->a->size); // going for radix sort
//		print_stack("After Sort", 0, ps->a, ps->b);
		//    ft_printf("Total number of instructions: %d\n", ps->n_ins);
	}
	clean_up_structs(ps);
	return (0);
}
