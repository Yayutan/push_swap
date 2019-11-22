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
# include "libft.h"
# include "get_next_line.h"
# include "stack.h"
# include "queue.h"
# include "instructions.h"
# include <limits.h>

typedef struct	s_ckr
{
	t_stack		*a;
	t_stack		*b;
	t_queue		*ins;
	int			v;
	int			c;
}				t_ckr;

int		*valid_int(char *str);
t_ckr	*setup_structs(void);
void	clean_up_structs(t_ckr *ckr);

#endif