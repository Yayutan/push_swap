/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:21:33 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/18 19:21:35 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char			*examine_sp_case(char *s1, char *s2)
{
	if ((!ft_strcmp(s1, "sa") && !ft_strcmp(s2, "sb")) || (!ft_strcmp(s1, "sb") && !ft_strcmp(s2, "sa")))
		return ("ss");
	else if ((!ft_strcmp(s1, "ra") && !ft_strcmp(s2, "rb")) || (!ft_strcmp(s1, "rb") && !ft_strcmp(s2, "ra")))
		return ("rr");
	else if ((!ft_strcmp(s1, "rra") && !ft_strcmp(s2, "rrb")) || (!ft_strcmp(s1, "rrb") && !ft_strcmp(s2, "rra")))
		return ("rrr");
	else
		return ("");
}

static void			eval_and_print_instructions(t_ps *ps)
{
	char	*cur;
	char	ins[4];

	while (ps->ins->head)
	{
		cur = dequeue(ps->ins);
		if (cur && front(ps->ins))
		{
			ft_strcpy(ins, examine_sp_case(cur, front(ps->ins)));
			if (!*ins)
				ft_printf("%s\n", cur);
			else
			{
				ft_printf("%s\n", ins);
				free(dequeue(ps->ins));
			}
			free(cur);
			cur = NULL;
		}
		if (cur)
		{
			ft_printf("%s\n", cur);
			free(cur);
		}
	}
}

static int			add_string_n(t_ps *ps, char **n)
{
	int		i;
	int		*nxt;

	i = 0;
	while (n[i + 1])
		i++;
	while (i >= 0)
	{
		nxt = NULL;
		if (!(nxt = valid_int(n[i])) || !(push(ps->a, *nxt)))
		{
			if (nxt)
				free(nxt);
			return (0);
		}
		if (nxt)
			free(nxt);
		i--;
	}
	return (1);
}

static t_stack		*check_num(t_ps *ps, int n_c, char **n_v)
{
	int		i;
	char	**n;

	i = n_c - 1;
	while (i >= 0)
	{
		n = ft_strsplit(n_v[i], ' ');
		if (!n)
			return (NULL);
		if (!*n || !(add_string_n(ps, n)))
		{
			clean_str_arr(n);
			return (NULL);
		}
		clean_str_arr(n);
		i--;
	}
	return (ps->a);
}

int					main(int ac, char **av)
{
	t_ps	*ps;

	ps = setup_structs();
	if (!check_num(ps, ac - 1, av + 1))
	{
		clean_up_structs(ps);
		ft_err_exit("Error");
	}
	ps->len = ps->a->size;
	if (ps->len > 1 && !check_sorted(ps->a))
	{
		if (!selection_sort(ps))
		{
			clean_up_structs(ps);
			ft_err_exit("Error");
		}
		(ps->len <= 5) ? sort_small(ps) : radix_sort(ps);
		eval_and_print_instructions(ps);
	}
	clean_up_structs(ps);
	return (0);
}
