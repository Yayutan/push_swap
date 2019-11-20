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

static t_queue		*get_instructions(t_queue *ins)
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

static t_stack		*check_num_input(t_stack *a, int n_c, char **n_v)
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

int		main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	t_queue	*ins;

	setup_structs(&a, &b, &ins);
	if(!check_num_input(a, argc - 1, argv + 1) || !get_instructions(ins))
	{
		clean_up_structs(a, b, ins);
		ft_err_exit("Error");
	}
//	execute_instruction(a, b, ins);
//	check_final_result(a, b);
	
	print_stack(a, b);
//	print_queue("INS", ins);
	clean_up_structs(a, b, ins);
	return (0);
}

//int		main(int argc, char **argv)
//{
//	argc++;
//	ft_putendl(argv[0]);
//	return (0);
//}