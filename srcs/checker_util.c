/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 19:03:59 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/19 19:04:37 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void		clean_ckr_structs(t_ckr *ckr)
{
	if (ckr->a)
		free_stack(ckr->a);
	if (ckr->b)
		free_stack(ckr->b);
	if (ckr->ins)
		free_queue(ckr->ins);
	if (ckr->ani)
		free_ani(ckr->ani);
	free(ckr);
}

t_ckr		*set_ckr_structs(void)
{
	t_ckr	*to_ret;

	if (!(to_ret = ft_memalloc(sizeof(t_ckr))))
		ft_err_exit("Failed to alllocate checker struct");
	to_ret->a = st_init();
	to_ret->b = st_init();
	to_ret->ins = q_init();
	if (!to_ret->a || !to_ret->b || !to_ret->ins)
	{
		if (to_ret->a)
			free_stack(to_ret->a);
		if (to_ret->b)
			free_stack(to_ret->b);
		if (to_ret->ins)
			free_queue(to_ret->ins);
		free(to_ret);
		ft_err_exit("Failed to alllocate stack and Q");
	}
	to_ret->v = 0;
	to_ret->c = 0;
	to_ret->fd = 0;
	to_ret->size = 0;
	return (to_ret);
}

int			parse_input_arg(t_ckr *ckr, char **n)
{
	int		i_v[2];
	int		*nxt;

	i_v[0] = 0;
	i_v[1] = 1;
	while (n[i_v[0]])
		i_v[0]++;
	while (i_v[1] && --i_v[0] >= 0)
	{
		nxt = NULL;
		if (!ft_strcmp("-v", n[i_v[0]]))
			ckr->v = 1;
		else if (!ft_strcmp("-c", n[i_v[0]]))
			ckr->c = 1;
		else if (!ft_strcmp("-f", n[i_v[0]]))
			ckr->fd = -1;
		else if (!ft_strcmp("-s", n[i_v[0]]))
			ckr->step_ani = 1;
		else if (!ft_strcmp("-a", n[i_v[0]]))
			ckr->auto_ani = 1;
		else if ((!(nxt = valid_int(n[i_v[0]])) || !(push(ckr->a, *nxt))))
			i_v[1] = 0;
		(nxt) ? free(nxt) : (nxt = NULL);
	}
	return (i_v[1]);
}

int			read_file(t_ckr *ckr)
{
	char	*file_name;

	if (ckr->fd == 0)
		return (0);
	ft_printf("Enter file to read, followed by <Enter>\n");
	file_name = NULL;
	if (get_next_line(0, &file_name) <= 0)
	{
		(file_name) ? free(file_name) : (file_name = NULL);
		return (-1);
	}
	return (open(file_name, O_RDONLY));
}

char		*concat_arguments(int argc, char **arg)
{
	int		i_len[2];
	char	*r_a[2];

	i_len[0] = -1;
	i_len[1] = argc - 1;
	while (++i_len[0] < argc)
	{
		r_a[1] = ft_strtrim(arg[i_len[0]]);
		i_len[1] += ft_strlen(r_a[1]);
		(r_a[1]) ? free(r_a[1]) : (r_a[1] = NULL);
	}
	r_a[0] = ft_strnew(i_len[1] + 1);
	i_len[1] = 0;
	while (++i_len[0] < (2 * argc + 1))
	{
		r_a[1] = ft_strtrim(arg[i_len[0] - argc - 1]);
		if (r_a[1])
		{
			ft_strncpy(r_a[0] + i_len[1], r_a[1], ft_strlen(r_a[1]));
			i_len[1] += ft_strlen(r_a[1]);
			r_a[0][i_len[1]++] = ' ';
			free(r_a[1]);
		}
	}
	return (r_a[0]);
}
