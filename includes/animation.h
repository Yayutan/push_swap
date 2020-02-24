/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:34:07 by mchuang           #+#    #+#             */
/*   Updated: 2020/01/20 16:34:09 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATION_H
# define ANIMATION_H
# include "../minilibx_macos/mlx.h"
# include "../libft/stack.h"
# include "../libft/queue.h"
# include "../libft/libft.h"
# include <time.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>

typedef struct		s_draw_util
{
	char			**xpm;
	int				max;
	double			sc[2];
	int				x;
	int				y;
	int				time_int;
	int				lock;
	int				steps;
}					t_draw_util;

typedef struct		s_ani
{
	void			*mlx;
	void			*win;
	void			*image;
	pthread_mutex_t	mutex;
	t_draw_util		*util;
}					t_ani;

t_ani				*animation(t_stack a);
void				draw_stacks(t_stack a, t_stack b, t_ani *ani);
void				draw_final_stack(t_stack a, t_ani *ani);
void				free_ani(t_ani *ani);

#endif
