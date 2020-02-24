/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_exe_ins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 10:52:32 by mchuang           #+#    #+#             */
/*   Updated: 2020/01/24 10:52:35 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void		draw_and_sleep(t_stack a, t_stack b, t_ani *ani, int size)
{
	draw_stacks(a, b, ani);
	pthread_mutex_lock(&ani->mutex);
	usleep((size <= 300) ? ani->util->time_int * 50000 : 250000);
	pthread_mutex_unlock(&ani->mutex);
}

int				auto_exe_ins(t_ckr *ckr)
{
	t_str_node	*cur;
	int			lock;

	if (ckr->v)
		print_stack("Init a and b", 0, ckr->a, ckr->b);
	draw_and_sleep(*(ckr->a), *(ckr->b), ckr->ani, ckr->size);
	cur = ckr->ins->head;
	while (cur)
	{
		pthread_mutex_lock(&ckr->ani->mutex);
		lock = (ckr->ani) ? ckr->ani->util->lock : 0;
		pthread_mutex_unlock(&ckr->ani->mutex);
		if (lock)
			continue ;
		ex_instruction(ckr->a, ckr->b, cur->data);
		if (ckr->v)
			print_stack(cur->data, ckr->c, ckr->a, ckr->b);
		draw_and_sleep(*(ckr->a), *(ckr->b), ckr->ani, ckr->size);
		cur = cur->next;
	}
	return (1);
}

int				step_exe_ins(t_ckr *ckr)
{
	t_str_node	*cur;
	int			steps;
	int			steps_to_do;

	steps = 0;
	if (ckr->v)
		print_stack("Init a and b", 0, ckr->a, ckr->b);
	draw_and_sleep(*(ckr->a), *(ckr->b), ckr->ani, ckr->size);
	cur = ckr->ins->head;
	while (cur)
	{
		pthread_mutex_lock(&ckr->ani->mutex);
		steps_to_do = ckr->ani->util->steps - steps;
		pthread_mutex_unlock(&ckr->ani->mutex);
		steps += steps_to_do;
		while (steps_to_do-- > 0)
		{
			ex_instruction(ckr->a, ckr->b, cur->data);
			if (ckr->v)
				print_stack(cur->data, ckr->c, ckr->a, ckr->b);
			draw_and_sleep(*(ckr->a), *(ckr->b), ckr->ani, ckr->size);
			cur = cur->next;
		}
	}
	return (1);
}

int				exe_ins(t_ckr *ckr)
{
	t_str_node	*cur;

	if (ckr->v)
		print_stack("Init a and b", 0, ckr->a, ckr->b);
	cur = ckr->ins->head;
	while (cur)
	{
		ex_instruction(ckr->a, ckr->b, cur->data);
		if (ckr->v)
			print_stack(cur->data, ckr->c, ckr->a, ckr->b);
		cur = cur->next;
	}
	return (1);
}

void			*get_ins(t_ckr *ckr)
{
	char		*line;
	int			ck;

	if ((ckr->fd = read_file(ckr)) < 0)
		return (NULL);
	ck = 0;
	while ((ck = get_next_line(ckr->fd, &line)) > 0)
	{
		if (find_index(line) < 0 || !enqueue(ckr->ins, line))
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
	return ((void*)ckr);
}
