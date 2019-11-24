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

static ins_f	**dispatch_table(void)
{
	ins_f	**f;

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
			return (i);
		i++;
	}
	free(ins_table);
	return (-1);
}

int				match_instruction(t_stack *a, t_stack *b, char *ins)
{
	int		i;
	ins_f	**f;

	i = find_index(ins);
	if (i < 0)
		return (-1);
	f = dispatch_table();
	f[i](a, b);
	free(f);
	return (1);
}

static void		print_helper(t_int_node *a, t_int_node *b, int c)
{
	char	*sa;
	char	*sb;
	int		wa;
	int		wb;

	sa = (a) ? ft_itoa(a->data) : ft_strnew(0);
	sb = (b) ? ft_itoa(b->data) : ft_strnew(0);
	wa = (11 - ft_strlen(sa)) / 2;
	wb = (14 - wa - ft_strlen(sa)) + ((11 - ft_strlen(sb)) / 2);
	if (c && a && a->red)
		ft_printf("%*s{RED}%s{CLEAR}", wa, "", sa);
	else
		ft_printf("%*s%s", wa, "", sa);
	if (c && b && b->red)
		ft_printf("%*s{RED}%s{CLEAR}\n", wb, "", sb);
	else
		ft_printf("%*s%s\n", wb, "", sb);
	if (a)
		a->red = 0;
	if (b)
		b->red = 0;
}

void			print_stack(char *ins, int c, t_stack *st_a, t_stack *st_b)
{
	t_int_node	*cur_a;
	t_int_node	*cur_b;

	ft_printf("Now executing ---> %s\n", ins);
	cur_a = (st_a) ? st_a->head : NULL;
	cur_b = (st_b) ? st_b->head : NULL;
	while (cur_a || cur_b)
	{
		print_helper(cur_a, cur_b, c);
		cur_a = (cur_a) ? cur_a->next : cur_a;
		cur_b = (cur_b) ? cur_b->next : cur_b;
	}
	ft_printf("-----------   -----------\n%6s%14s\n\n", "a", "b");
}
