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

static int			auto_exe_ins(t_ckr *ckr)
{
	t_str_node	*cur;
	int			lock;

	if (ckr->v)
		print_stack("Init a and b", 0, ckr->a, ckr->b);
	if (ckr->auto_ani)
	{
		draw_stacks(*(ckr->a), *(ckr->b), ckr->ani);
		usleep(ckr->ani->util->time_int * 50000);
	}
	cur = ckr->ins->head;
	while (cur)
	{
		pthread_mutex_lock(&g_lock);
		lock = (ckr->ani) ? ckr->ani->util->lock : 0;
		pthread_mutex_unlock(&g_lock);
		if (lock)
			continue ;
		ex_instruction(ckr->a, ckr->b, cur->data);
		if (ckr->v)
			print_stack(cur->data, ckr->c, ckr->a, ckr->b);
		if (ckr->auto_ani)
		{
			draw_stacks(*(ckr->a), *(ckr->b), ckr->ani);
			usleep(ckr->ani->util->time_int * 50000);
		}
		cur = cur->next;
	}
	return (1);
}

static int			step_exe_ins(t_ckr *ckr)
{
	t_str_node	*cur;
	int			steps;
	int			steps_to_do;

	steps = 0;
	if (ckr->v)
		print_stack("Init a and b", 0, ckr->a, ckr->b);
	draw_stacks(*(ckr->a), *(ckr->b), ckr->ani);
	usleep(ckr->ani->util->time_int * 50000);
	cur = ckr->ins->head;
	while (cur)
	{
		pthread_mutex_lock(&g_steps);
		steps_to_do = ckr->ani->util->steps - steps;
		pthread_mutex_unlock(&g_steps);
		steps += steps_to_do;
		while (steps_to_do > 0)
		{
			ex_instruction(ckr->a, ckr->b, cur->data);
			if (ckr->v)
				print_stack(cur->data, ckr->c, ckr->a, ckr->b);
			draw_stacks(*(ckr->a), *(ckr->b), ckr->ani);
			usleep(ckr->ani->util->time_int * 50000);
			cur = cur->next;
			steps_to_do--;
		}
	}
	return (1);
}

static t_ckr		*get_ins(t_ckr *ckr)
{
	char		*line;
	int			ck;

	if ((ckr->fd = read_file(ckr)) < 0)
		return (NULL);
	ck = 0;
	while ((ck = get_next_line(ckr->fd, &line)) > 0)
	{
		if (find_index(line) < 0|| !enqueue(ckr->ins, line))
		{
			if (line)
				free(line);
			return (NULL);
		}
		if (line)
			free(line);
	}
	if (ck < 0)
		return (NULL);
	return (ckr);
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
	return (ckr->a);
}


static void			*checker(void *args)
{
	t_ckr	*ckr;

	ckr = (t_ckr*)args;
	if ((!ckr->step_ani && !auto_exe_ins(ckr)))
	{
		clean_ckr_structs(ckr);
		ft_err_exit("Error");
	}
	else if ((ckr->step_ani && !step_exe_ins(ckr)))
	{
		clean_ckr_structs(ckr);
		ft_err_exit("Error");
	}	
	(check_final_result(ckr->a, ckr->b)) ? ft_putendl("OK") : ft_putendl("KO");
	clean_ckr_structs(ckr);
	return (NULL);
}

int					main(int ac, char **av)
{
	pthread_t 		tid;
	pthread_attr_t	attr;
	t_ckr			*ckr;

	ckr = set_ckr_structs();
	if (!setup_init_st(ckr, ac, av))
	{
		clean_ckr_structs(ckr);
		ft_err_exit("Error");
	}
	if (ckr->a->size > 0)
	{
		if (!get_ins(ckr))
		{
			clean_ckr_structs(ckr);
			ft_err_exit("Error");
		}
		if (ckr->step_ani || ckr->auto_ani)
		{
			if (!(ckr->ani = animation(*(ckr->a), *(ckr->b))))
			ft_err_exit("Failed to setup mlx");
			pthread_attr_init(&attr);
			pthread_create(&tid, &attr, &checker, ckr);
			mlx_loop(ckr->ani->mlx);
		}
		else
			checker(ckr);
	}
	return (0);
}
