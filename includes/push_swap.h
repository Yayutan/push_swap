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
# include "general_util.h"
# include <limits.h>

typedef struct	s_ps
{
	t_stack		*a;
	t_stack		*b;
	int			len;
	int			n_parts;
	int			sym_p_pt;
	int			n_symbols;
	int			max_symbols;

}				t_ps;

void			selection_sort(t_stack *a);
void			calc_m_and_sort(t_ps *ps);

#endif
