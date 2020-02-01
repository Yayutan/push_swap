/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:21:28 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/18 19:21:31 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int			check_final_result(t_stack *a, t_stack *b)
{
	t_int_node	*cur;

	if (b->size != 0)
		return (0);
	if (a->size == 1)
		return (1);
	cur = a->head;
	while (cur->next)
	{
		if (cur->data > cur->next->data)
			return (0);
		cur = cur->next;
	}
	return (1);
}

static void			*checker(void *args)
{
	t_ckr	*ckr;
	int		sucess;

	ckr = (t_ckr*)args;
	sucess = 0;
	if (!ckr->auto_ani && !ckr->step_ani)
		sucess = exe_ins(ckr);
	else if (ckr->auto_ani)
		sucess = auto_exe_ins(ckr);
	else if (ckr->step_ani)
		sucess = step_exe_ins(ckr);
	if (!sucess)
	{
		clean_ckr_structs(ckr);
		ft_err_exit("Error");
	}
	sucess = check_final_result(ckr->a, ckr->b);
	if (sucess)
	{
		if (ckr->step_ani || ckr->auto_ani)
			draw_final_stack(*(ckr->a), ckr->ani);
	}
	ft_putendl((sucess) ? "OK" : "KO");
	clean_ckr_structs(ckr);
	return (NULL);
}

static void			multi_thread_animaiton(t_ckr *ckr)
{
	pthread_t		tid;
	pthread_attr_t	attr;
	void			*mlx;

	if (!(ckr->ani = animation(*(ckr->a))))
	{
		clean_ckr_structs(ckr);
		ft_err_exit("Failed to setup mlx");
	}
	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, &checker, ckr);
	mlx = ckr->ani->mlx;
	mlx_loop(mlx);
}

static t_stack		*setup_init_st(t_ckr *ckr, int n_c, char **n_v)
{
	char	**n;
	char	*arg;

	arg = concat_arguments((n_c - 1), (n_v + 1));
	n = ft_strsplit(arg, ' ');
	if (!n)
		return (NULL);
	if (!*n || !(parse_input_arg(ckr, n)))
	{
		clean_str_arr(n);
		return (NULL);
	}
	clean_str_arr(n);
	ckr->size = ckr->a->size;
	return (ckr->a);
}

int					main(int ac, char **av)
{
	t_ckr			*ckr;

	ckr = set_ckr_structs();
	if (ac > 2 && !setup_init_st(ckr, ac, av))
	{
		clean_ckr_structs(ckr);
		ft_err_exit("Error");
	}
	if (ckr->size > 0)
	{
		if (!get_ins(ckr))
		{
			clean_ckr_structs(ckr);
			ft_err_exit("Error");
		}
		if (ckr->step_ani || ckr->auto_ani)
			multi_thread_animaiton(ckr);
		else
			checker(ckr);
	}
	return (0);
}
