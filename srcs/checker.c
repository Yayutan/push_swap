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

static int			exe_ins(t_ckr *ckr)
{
	t_str_node	*cur;

	if (ckr->v)
		print_stack("Init a and b", 0, ckr->a, ckr->b);
	cur = ckr->ins->head;
	while (cur)
	{
		if (ex_instruction(ckr->a, ckr->b, cur->data) < 0)
			return (0);
		if (ckr->v)
			print_stack(cur->data, ckr->c, ckr->a, ckr->b);
		cur = cur->next;
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
		if (!enqueue(ckr->ins, line))
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

	arg = concat_arguments(n_c, n_v);
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

int					main(int ac, char **av)
{
	t_ckr	*ckr;

	ckr = set_ckr_structs();
	if (!setup_init_st(ckr, ac - 1, av + 1))
	{
		clean_ckr_structs(ckr);
		ft_err_exit("Error");
	}
	if (ckr->a->size > 0)
	{
		if (!get_ins(ckr) || !exe_ins(ckr))
		{
			clean_ckr_structs(ckr);
			ft_err_exit("Error");
		}
		if (check_final_result(ckr->a, ckr->b))
			ft_printf("OK\n");
		else
			ft_printf("KO\n");
	}
	clean_ckr_structs(ckr);
	return (0);
}
