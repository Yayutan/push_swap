/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 10:32:59 by mchuang           #+#    #+#             */
/*   Updated: 2020/01/24 10:33:01 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animation.h"

static void			clear_rest_xpm(t_draw_util *util, int i)
{
	int				r;
	int				c;

	r = 3 + (int)((i - 1) * util->sc[1]);
	while (r < 563)
	{
		c = 0;
		while (c < 700)
		{
			util->xpm[r][c] = '0';
			c++;
		}
		r++;
	}
}

static void			paint(t_int_node **nd, t_draw_util *util, int index)
{
	int				c;
	int				r;

	c = 0;
	while (c < 700)
	{
		if (nd[0] && (c < 325) & (c < nd[0]->data * util->sc[0]))
			(util->xpm)[3 + (int)((index - 1) * util->sc[1])][c] = '1';
		else if (nd[1] && (c >= 375) && (c < 375 + nd[1]->data * util->sc[0]))
			(util->xpm)[3 + (int)((index - 1) * util->sc[1])][c] = '1';
		else
			(util->xpm)[3 + (int)((index - 1) * util->sc[1])][c] = '0';
		c++;
	}
	r = 1;
	while (r < util->sc[1])
	{
		ft_strcpy((util->xpm)[3 + (int)((index - 1) * util->sc[1]) + r],
			(util->xpm)[3 + (int)((index - 1) * util->sc[1])]);
		r++;
	}
}

void				draw_stacks(t_stack a, t_stack b, t_ani *ani)
{
	t_int_node		*cur[2];
	int				i;

	if (ani->image)
		mlx_destroy_image(ani->mlx, ani->image);
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
	ani->image = mlx_xpm_to_image(ani->mlx,
		(char**)ani->util->xpm, &(ani->util->y), &(ani->util->x));
	mlx_put_image_to_window(ani->mlx, ani->win, ani->image, 25, 20);
	mlx_do_sync(ani->mlx);
}

void				draw_final_stack(t_stack a, t_ani *ani)
{
	t_int_node		*cur[2];
	int				i;

	if (ani->image)
		mlx_destroy_image(ani->mlx, ani->image);
	cur[0] = a.head;
	cur[1] = NULL;
	ani->util->xpm[2] = ft_strdup("1 c #00ff00");
	i = 1;
	while (cur[0])
	{
		paint(cur, ani->util, i);
		cur[0] = cur[0]->next;
		i++;
	}
	clear_rest_xpm(ani->util, i);
	ani->image = mlx_xpm_to_image(ani->mlx,
		(char**)ani->util->xpm, &(ani->util->y), &(ani->util->x));
	mlx_put_image_to_window(ani->mlx, ani->win, ani->image, 25, 20);
	mlx_do_sync(ani->mlx);
}
