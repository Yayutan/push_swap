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

int					main(int ac, char **av)
{
	t_ps	*ps;

	ps = setup_structs();
	if (!check_num(ps, ac - 1, av + 1))
	{
		clean_up_structs(ps);
		ft_err_exit("Error");
	}
	if (ps->a->size > 0)
	{
		if (!selection_sort(ps))
		{
			clean_up_structs(ps);
			ft_err_exit("Error");
		}
		sort(ps);
	}
	clean_up_structs(ps);
	return (0);
}
