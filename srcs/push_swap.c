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

static t_stack		*check_num(t_ps *ps, int n_c, char **n_v)
{
	int		i;
	int		*nxt;

	i = n_c - 1;
	while (i >= 0)
	{
		nxt = NULL;
		if (!(nxt = valid_int(n_v[i])) || !(push(ps->st, *nxt)))
		{
			if (nxt)
				free(nxt);
			return (NULL);
		}
		if (nxt)
			free(nxt);
		i--;
	}
	return (ps->st);
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
	print_stack("Init a", 0, ps->st, NULL);
	clean_up_structs(ps);
	return (0);

}
