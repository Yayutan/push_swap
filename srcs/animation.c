/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:33:56 by mchuang           #+#    #+#             */
/*   Updated: 2020/01/20 16:33:58 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animation.h"

static int		find_max(t_stack a)
{
	int			max;
	t_int_node	*cur;

	cur = a.head;
	max = INT_MIN;
	while (cur)
	{
		if (cur->data > max)
			max = cur->data;
		cur = cur->next;
	}
	return (max);
}

static t_draw_util	*setup_draw(t_stack a) // err chk , del func
{
	t_draw_util		*to_ret;
	int				i;

	to_ret = (t_draw_util*)ft_memalloc(sizeof(t_draw_util));
	to_ret->xpm = (char**)ft_memalloc(sizeof(char*) * 563);
	to_ret->xpm[0] = ft_strdup("700 560 2 1");
	to_ret->xpm[1] = ft_strdup("0 c #000000");
	to_ret->xpm[2] = ft_strdup("1 c #ffcc00");
	i = 3;
	while (i < 563)
	{
		to_ret->xpm[i] = ft_strnew(700);
		i++;
	}
	to_ret->time_int = 3;
	to_ret->max = find_max(a);
	to_ret->size_x = 700;
	to_ret->size_y = 560;
	to_ret->scale[0] = 325.0 / to_ret->max;
	to_ret->scale[1] = 560.0 / a.size;
	to_ret->lock = 0;
	to_ret->steps = 0;
	return (to_ret);
}

static int			key_handler(int k, t_ani *ani)
{
	pthread_mutex_lock(&g_lock);
	if (k == 53)
		exit(0);
	else if (k == 116)
		ani->util->time_int -= (ani->util->time_int > 1) ? 1 : 0;
	else if (k == 121)
		ani->util->time_int += (ani->util->time_int < 10) ? 1 : 0;
	else if (k == 49)
	{		
	
		if (ani->util->lock)
			ani->util->lock = 0;
		else
		{
			ani->util->lock = 1;
			mlx_string_put (ani->mlx, ani->win, 20, 20, 0xff0000, "PAUSED");
		}		
	}
	else if (k == 1)
		ani->util->steps++;	
	pthread_mutex_unlock(&g_lock);
	return (0);
}

t_ani	*animation(t_stack a)
{
	t_ani	*ani;

	if (!(ani = (t_ani*)ft_memalloc(sizeof(t_ani))))
		return (NULL);
	ani->util = setup_draw(a);
	ani->mlx = mlx_init();
	ani->win = mlx_new_window(ani->mlx, 750, 600, "push_swap");
	mlx_key_hook(ani->win, key_handler, ani);
	return (ani);
}
