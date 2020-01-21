/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:21:05 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/18 19:21:13 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "../libft/stack.h"
# include "../libft/queue.h"
# include "instructions.h"
# include "general_util.h"
# include "animation.h"
# include <limits.h>
# include <fcntl.h>

typedef struct	s_ckr
{
	t_stack		*a;
	t_stack		*b;
	t_queue		*ins;
	t_ani		*ani;
	int			v;
	int			c;
	int			step_ani;
	int			auto_ani;
	int			fd;
}				t_ckr;

t_ckr			*set_ckr_structs(void);
char			*concat_arguments(int argc, char **arg);
void			clean_ckr_structs(t_ckr *ckr);
int				parse_input_arg(t_ckr *ckr, char **n);
int				read_file(t_ckr *ckr);

#endif
