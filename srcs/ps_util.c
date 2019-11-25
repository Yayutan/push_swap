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

void					clean_up_structs(t_ps *ps)
{
	free_stack(ps->st);
	free(ps);
}

t_ps					*setup_structs(void)
{
	t_ps	*to_ret;

	if (!(to_ret = ft_memalloc(sizeof(t_ps))))
		ft_err_exit("Failed to alllocate checker struct");
	if (!(to_ret->st = st_init()))
	{
		free(to_ret);
		ft_err_exit("Failed to alllocate stack A");
	}
	return (to_ret);
}
