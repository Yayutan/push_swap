/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:46:08 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/20 19:47:21 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"

static char		**instruction_table(void)
{
	char	**ins_table;

	ins_table = ft_memalloc(sizeof(*ins_table) * 11);
	ins_table[0] = "sa";
	ins_table[1] = "sb";
	ins_table[2] = "ss";
	ins_table[3] = "pa";
	ins_table[4] = "pb";
	ins_table[5] = "ra";
	ins_table[6] = "rb";
	ins_table[7] = "rr";
	ins_table[8] = "rra";
	ins_table[9] = "rrb";
	ins_table[10] = "rrr";
	return (ins_table);
}

static t_ins_f	**dispatch_table(void)
{
	t_ins_f	**f;

	f = ft_memalloc(sizeof(*f) * 11);
	f[0] = &sa;
	f[1] = &sb;
	f[2] = &ss;
	f[3] = &pa;
	f[4] = &pb;
	f[5] = &ra;
	f[6] = &rb;
	f[7] = &rr;
	f[8] = &rra;
	f[9] = &rrb;
	f[10] = &rrr;
	return (f);
}

static int		find_index(char *ins)
{
	char	**ins_table;
	int		i;

	ins_table = instruction_table();
	i = 0;
	while (i < 11)
	{
		if (!ft_strcmp(ins_table[i], ins))
		{
			free(ins_table);
			return (i);
		}
		i++;
	}
	free(ins_table);
	return (-1);
}

void			pt_instruction(t_stack *a, t_stack *b, char *ins)
{
	int		i;
	t_ins_f	**f;

	i = find_index(ins);
	f = dispatch_table();
	ft_printf("%s\n", ins);
	f[i](a, b);
	free(f);
}

int				ex_instruction(t_stack *a, t_stack *b, char *ins)
{
	int		i;
	t_ins_f	**f;

	i = find_index(ins);
	if (i < 0)
		return (-1);
	f = dispatch_table();
	f[i](a, b);
	free(f);
	return (1);
}
