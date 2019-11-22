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
    t_str_node  *cur;

	if (ckr->v)
		print_stack("Init a and b", ckr->a, ckr->b);
    cur = ckr->ins->head;
    while (cur)
    {
        if (match_instruction(ckr->a, ckr->b, cur->data) < 0)
            return (0);
		if (ckr->v)
			print_stack(cur->data, ckr->a, ckr->b);
        cur = cur->next;
    }
    return (1);
}

static t_queue		*get_ins(t_queue *ins)
{
	char		*line;
	int			ck;
	
	ck = 0;
	while ((ck = get_next_line(0, &line)) > 0)
	{
		if(!enqueue(ins, line))
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
	return (ins);
}

static t_stack		*check_num(t_ckr *ckr, int n_c, char **n_v)
{
	int		i;
	int		*nxt;

	i = n_c - 1;
	while (i >= 0)
	{
		nxt = NULL;
		if (!ft_strcmp("-v", n_v[i]))
			ckr->v = 1;
		else if (!ft_strcmp("-c", n_v[i]))
			ckr->c = 1;
		else if (!(nxt = valid_int(n_v[i])) || !(push(ckr->a, *nxt)))
		{
			if (nxt)
				free(nxt);
			return (NULL);		
		}
		if (nxt)
			free(nxt);
		i--;
	}
	return (ckr->a);
}

int					main(int ac, char **av)
{
	t_ckr	*ckr;

	ckr = setup_structs();
	if(!check_num(ckr, ac - 1, av + 1) || !get_ins(ckr->ins) || !exe_ins(ckr))
	{
		clean_up_structs(ckr);
		ft_err_exit("Error");
	}
	if (check_final_result(ckr->a, ckr->b))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	clean_up_structs(ckr);
	return (0);
}
