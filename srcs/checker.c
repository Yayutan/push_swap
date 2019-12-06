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
		///
//		print_stack("B4 match function call", 0, ckr->a, ckr->b);
		///
		if (match_instruction(ckr->a, ckr->b, cur->data) < 0)
			return (0);
		if (ckr->v)
			print_stack(cur->data, ckr->c, ckr->a, ckr->b);
		cur = cur->next;
	}
	return (1);
}

//static t_queue		*get_ins(t_queue *ins)
static t_queue		*get_ins(t_ckr *ckr)
{
	char		*line;
	int			ck;

	ck = 0;
	while ((ck = get_next_line(0, &line)) > 0)
	{
		
		///
//		print_stack("Before enqueue", 0, ckr->a, ckr->b);
		///
		
		if (!enqueue(ckr->ins, line))
//		if (!enqueue(ins, line))
		{
			if (line)
				free(line);
			return (NULL);
		}
		if (line)
			free(line);
				
		///
//		print_stack("After enqueue", 0, ckr->a, ckr->b);
		///
		
	}
	if (ck < 0)
		return (NULL);
	return (ckr->ins);
//	return (ins);
}

static t_stack		*check_num(t_ckr *ckr, int n_c, char **n_v)
{
	int		i;
	char	**n;

	i = n_c - 1;
	while (i >= 0)
	{
		if (!ft_strcmp("-v", n_v[i]))
			ckr->v = 1;
		else if (!ft_strcmp("-c", n_v[i]))
			ckr->c = 1;
		else
		{
			n = ft_strsplit(n_v[i], ' ');
			if (!n)
				return (NULL);
			if (!*n || !(add_string_n(ckr, n)))
			{
				clean_str_arr(n);
				return (NULL);
			}
			clean_str_arr(n);
		}
		i--;
	}
	return (ckr->a);
}

int					main(int ac, char **av)
{
	t_ckr	*ckr;

	ckr = setup_structs();
	if (!check_num(ckr, ac - 1, av + 1))
	{
		clean_up_structs(ckr);
		ft_err_exit("Error");
	}
	
	///
//	print_stack("Initial a and b", 0, ckr->a, ckr->b);
	///
	
	if (ckr->a->size > 0)
	{
		if (!get_ins(ckr) || !exe_ins(ckr))
//		if (!get_ins(ckr->ins) || !exe_ins(ckr))
		{
			clean_up_structs(ckr);
			ft_err_exit("Error");
		}
		
		///
//		print_stack("Final a and b", 0, ckr->a, ckr->b);
		///
		
		if (check_final_result(ckr->a, ckr->b))
			ft_printf("OK\n");
		else
			ft_printf("KO\n");
	}
	clean_up_structs(ckr);
	return (0);
}
