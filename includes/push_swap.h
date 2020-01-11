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
	t_int_node	**sorted;
	int			len;
	int			n_parts;
	int			sym_p_pt;
	int			layer;
	int			max_symbols;

}				t_ps;

t_ps			*setup_structs(void);
void			clean_up_structs(t_ps *ps);
int				check_sorted(t_stack *st);
int				selection_sort(t_ps *ps);
void			radix_sort(t_ps *ps);
void			sort_small(t_ps *ps);
int				log_m_ceil(int n, int m);
int				exponential(int b, int p);
void			update_index(t_ps *ps, int end_b);
void			final_ord_rev(t_ps *ps);
void			final_ord(t_ps *ps);

#endif
