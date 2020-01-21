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

# include <time.h>
# include <stdio.h>

int			key_handler(int k, t_draw_util *util)
{
	if (k == 53)
		exit(0);
	else if (k == 116)
		util->time_int -= (util->time_int > 1) ? 1 : 0;
	else if (k == 121)
		util->time_int += (util->time_int < 10) ? 1 : 0;
	else if (k == 49)
	{		
		if (util->lock)
		{
			printf("Unlocked\n");
			util->lock = 0;
			pthread_mutex_unlock(&g_lock);	
		}
		else
		{
			printf("Locked\n");
			util->lock = 1;
			pthread_mutex_lock(&g_lock);
		}
	}
	// printf("%d\n", k);
	return (0);
}

static int		find_max(t_stack a, t_stack b)
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
	cur = b.head;
	while (cur)
	{
		if (cur->data > max)
			max = cur->data;
		cur = cur->next;
	}
	return (max);
}

// static int		find_min(t_stack a, t_stack b)
// {
// 	int			min;
// 	t_int_node	*cur;

// 	cur = a.head;
// 	min = INT_MAX;
// 	while (cur)
// 	{
// 		if (cur->data < min)
// 			min = cur->data;
// 		cur = cur->next;
// 	}
// 	cur = b.head;
// 	while (cur)
// 	{
// 		if (cur->data < min)
// 			min = cur->data;
// 		cur = cur->next;
// 	}
// 	return (min);
// }

static void			clear_rest_xpm(t_draw_util *util, int i)
{
	int		r;
	int		c;

	r = 3 + (i - 1) * util->scale[1];
	while (r < 443)
	{
		c = 0;
		while (c < 440)
		{
			util->xpm[r][c] = '0';			
			c++;
		}
		r++;
	}
}

static t_draw_util	*setup_draw(t_stack a, t_stack b) // err chk , del func
{
	t_draw_util		*to_ret;
	int				i;

	to_ret = (t_draw_util*)ft_memalloc(sizeof(t_draw_util));
	to_ret->xpm = (char**)ft_memalloc(sizeof(char*) * 443);
	to_ret->xpm[0] = ft_strdup("440 440 2 1");
	to_ret->xpm[1] = ft_strdup("0 c #000000");
	to_ret->xpm[2] = ft_strdup("1 c #00ff00");
	i = 3;
	while (i < 443)
	{
		to_ret->xpm[i] = ft_strnew(440);
		i++;
	}
	to_ret->time_int = 2;
	to_ret->max = find_max(a, b);
	to_ret->min = 0; /*find_min(a, b); neg num??*/
	to_ret->size_x = 440;
	to_ret->size_y = 440;
	to_ret->scale[0] = 220 / (to_ret->max - to_ret->min);
	to_ret->scale[1] = 440 / (a.size + b.size);
	to_ret->lock = 0;
	return (to_ret);
}

static void		paint(t_int_node **node, t_draw_util *util, int index)
{
	int		c;
	int		r;
	
	c = 0;
	while (c < 440)
	{
		if (node[0] && (c < 220) & (c < node[0]->data * util->scale[0]))
			(util->xpm)[3 + (index - 1) * util->scale[1]][c] = '1';
		else if(node[1] && (c >= 220) && (c < 220 + node[1]->data * util->scale[0]))
			(util->xpm)[3 + (index - 1) * util->scale[1]][c] = '1';
		else
			(util->xpm)[3 + (index - 1) * util->scale[1]][c] = '0';
		c++;
	}
	r = 1;
	while (r < util->scale[1])
	{
		ft_strcpy((util->xpm)[3 + (index - 1) * util->scale[1] + r],
			(util->xpm)[3 + (index - 1) * util->scale[1]]);
		r++;
	}
}

void		draw_stacks(t_stack a, t_stack b, t_ani *ani)
{
	t_int_node			*cur[2];
	int					i;
	void				*img; // put outside to free?

	cur[0] = a.head;
	cur[1] = b.head;
	i = 1;
	while (cur[0] || cur[1])
	{
		paint(cur, ani->util, i);
		cur[0] = (cur[0]) ? cur[0]->next : NULL;
		cur[1] = (cur[1]) ? cur[1]->next : NULL;	
		i++;
	}
	clear_rest_xpm(ani->util, i);	
	img = mlx_xpm_to_image(ani->mlx, (char**)ani->util->xpm, &(ani->util->size_y), &(ani->util->size_x));
	mlx_put_image_to_window(ani->mlx, ani->win, img, 20, 20);
}

t_ani	*animation(t_stack a, t_stack b)
{
	t_ani	*ani;

	if (!(ani = (t_ani*)ft_memalloc(sizeof(t_ani))))
		return (NULL);
	ani->util = setup_draw(a, b);
	ani->mlx = mlx_init();
	ani->win = mlx_new_window(ani->mlx, 500, 500, "push_swap");
	mlx_key_hook(ani->win, key_handler, ani->util);
	return (ani);
}
