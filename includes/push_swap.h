/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:21:16 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/18 19:21:18 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft.h"
# include "stack.h"
# include "queue.h"
# include "instructions.h"
# include <limits.h>

typedef struct	s_ps
{
	t_stack		*st;
}				t_ps;

t_ps	*setup_structs(void);
void	clean_up_structs(t_ps *ps);

#endif