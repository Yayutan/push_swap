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

// void	test_image(void *mlx, void *win)
// {
// 	char	*xpm[] = {
// 	/* <Values> */
// 	/* <width/columns> <height/rows> <colors> <chars per pixel>*/
// 	"48 16 3 1",
// 	/* <Colors> */
// 	"a c #ffffff",
// 	"b c #ff0000",
// 	"d c #00ff00",
// 	/* <Pixels> */
// 	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
// 	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
// 	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
// 	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
// 	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
// 	"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
// 	"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
// 	"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
// 	"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
// 	"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
// 	"dddddddddddddddddddddddddddddddddddddddddddddddd",
// 	"dddddddddddddddddddddddddddddddddddddddddddddddd",
// 	"dddddddddddddddddddddddddddddddddddddddddddddddd",
// 	"dddddddddddddddddddddddddddddddddddddddddddddddd",
// 	"dddddddddddddddddddddddddddddddddddddddddddddddd",
// 	"dddddddddddddddddddddddddddddddddddddddddddddddd"
// 	};
// 	int		x = 48;
// 	int		y = 16;
// 	void	*image = mlx_xpm_to_image(mlx, xpm, &x, &y);
// 	mlx_put_image_to_window(mlx, win, image, 10, 10);
// }

// void	test_image_2(void *mlx, void *win)
// {
// 	char	*xpm[] = {
// 	/* <Values> */
// 	/* <width/columns> <height/rows> <colors> <chars per pixel>*/
// 	"48 16 3 1",
// 	/* <Colors> */
// 	"a c #ffffff",
// 	"b c #ff0000",
// 	"d c #00ff00",
// 	/* <Pixels> */
// 	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
// 	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
// 	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
// 	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
// 	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
// 	"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
// 	"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
// 	"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
// 	"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
// 	"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
// 	"dddddddddddddddddddddddddddddddddddddddddddddddd",
// 	"dddddddddddddddddddddddddddddddddddddddddddddddd",
// 	"dddddddddddddddddddddddddddddddddddddddddddddddd",
// 	"dddddddddddddddddddddddddddddddddddddddddddddddd",
// 	"dddddddddddddddddddddddddddddddddddddddddddddddd",
// 	"dddddddddddddddddddddddddddddddddddddddddddddddd"
// 	};
// 	int		x = 48;
// 	int		y = 16;
// 	void	*image = mlx_xpm_to_image(mlx, xpm, &x, &y);
// 	mlx_put_image_to_window(mlx, win, image, 100, 100);
// }

int			key_handler(int k, t_draw_util *util)
{
	if (k == 53)
		exit(0);
	else if (k == 116)
		util->time_int -= (util->time_int > 1) ? 1 : 0;
	else if (k == 121)
		util->time_int += (util->time_int < 10) ? 1 : 0;
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

static int		find_min(t_stack a, t_stack b)
{
	int			min;
	t_int_node	*cur;

	cur = a.head;
	min = INT_MAX;
	while (cur)
	{
		if (cur->data < min)
			min = cur->data;
		cur = cur->next;
	}
	cur = b.head;
	while (cur)
	{
		if (cur->data < min)
			min = cur->data;
		cur = cur->next;
	}
	return (min);
}

static void			clear_xpm(char **xpm)
{
	int		r;
	int		c;

	r = 3;
	while (r < 443)
	{
		c = 0;
		while (c < 440)
		{
			xpm[r][c] = '0';
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
	to_ret->time_int = 4;
	to_ret->max = find_max(a, b);
	to_ret->min = find_min(a, b);
	to_ret->size_x = 440;
	to_ret->size_y = 440;
	to_ret->scale[0] = 220 / (to_ret->max - to_ret->min);
	to_ret->scale[1] = 440 / (a.size + b.size);
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
	r = 0;
	while (r < util->scale[1])
	{
		ft_strcpy((util->xpm)[3 + (index - 1) * util->scale[1] + r],
			(util->xpm)[3 + (index - 1) * util->scale[1]]);
		r++;
	}
	
}

void		draw_stacks(t_stack a, t_stack b, t_ani *ani)
{ // put image in exe, faster?
	t_int_node			*cur[2];
	int					i;
	void				*img; // put outside to free?

	clear_xpm(ani->util->xpm);
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



// void	*child_thread(void *args)
// {
// 	t_ani *ani = (t_ani*)args;
// 	test_image(ani->mlx, ani->win);
// 	sleep(5); ///// key hook to change time interval (set restrictions)
// 	////// mutex to pause/resume
// 	test_image_2(ani->mlx, ani->win);
// 	return (NULL);
// }