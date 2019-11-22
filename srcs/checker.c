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

static int			exe_ins(t_stack *a, t_stack *b, t_queue *ins)
{
    t_str_node  *cur;

	print_stack("Init a and b", a, b);
    cur = ins->head;
    while (cur)
    {
        if (match_instruction(a, b, cur->data) < 0)
            return (0);
		print_stack(cur->data, a, b);
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

static t_stack		*check_num(t_stack *a, int n_c, char **n_v)
{
	int		i;
	int		*nxt;

	i = n_c - 1;
	while (i >= 0)
	{
		if (!(nxt = valid_int(n_v[i])) || !(push(a, *nxt)))
		{
			if (nxt)
				free(nxt);
			return (NULL);		
		}
		free(nxt);
		i--;
	}
	return (a);
}

int					main(int ac, char **av)
{
	t_stack	*a;
	t_stack	*b;
	t_queue	*ins;

	setup_structs(&a, &b, &ins);
	if(!check_num(a, ac - 1, av + 1) || !get_ins(ins) || !exe_ins(a, b, ins))
	{
		clean_up_structs(a, b, ins);
		ft_err_exit("Error");
	}
	if (check_final_result(a, b))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	clean_up_structs(a, b, ins);
	return (0);
}
