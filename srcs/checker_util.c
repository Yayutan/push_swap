/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 19:03:59 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/19 19:04:37 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void		clean_ckr_structs(t_ckr *ckr)
{
	free_stack(ckr->a);
	free_stack(ckr->b);
	free_queue(ckr->ins);
	free(ckr);
}

t_ckr		*set_ckr_structs(void)
{
	t_ckr	*to_ret;

	if (!(to_ret = ft_memalloc(sizeof(t_ckr))))
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
	if (!(to_ret->ins = q_init()))
	{
		free_stack(to_ret->a);
		free_stack(to_ret->b);
		free(to_ret);
		ft_err_exit("Failed to alllocate instruction Q");
	}
	to_ret->v = 0;
	to_ret->c = 0;
	return (to_ret);
}

int			parse_input_arg(t_ckr *ckr, char **n)
{
	int		i;
	int		*nxt;

	i = 0;
	while (n[i])
		i++;
	i--;
	while (i >= 0)
	{
		nxt = NULL;
		if (!ft_strcmp("-v", n[i]))
			ckr->v = 1;
		else if (!ft_strcmp("-c", n[i]))
			ckr->c = 1;
		else if (!(nxt = valid_int(n[i])) || !(push(ckr->a, *nxt)))
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
