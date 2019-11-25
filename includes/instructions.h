/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 20:17:08 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/20 20:17:11 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTIONS_H
# define INSTRUCTIONS_H
# include "ft_printf.h"
# include "stack.h"
# include "queue.h"

typedef void	(ins_f)(t_stack *st1, t_stack *st2);

void		sa(t_stack *a, t_stack *b);
void		sb(t_stack *a, t_stack *b);
void		ss(t_stack *a, t_stack *b);
void		pa(t_stack *a, t_stack *b);
void		pb(t_stack *a, t_stack *b);
void		ra(t_stack *a, t_stack *b);
void		rb(t_stack *a, t_stack *b);
void		rr(t_stack *a, t_stack *b);
void		rra(t_stack *a, t_stack *b);
void		rrb(t_stack *a, t_stack *b);
void		rrr(t_stack *a, t_stack *b);
void		do_instruction(t_stack *a, t_stack *b, char *ins);
int			match_instruction(t_stack *a, t_stack *b, char *ins);
void		print_stack(char *info, int c, t_stack *st_a, t_stack *st_b);
int			*valid_int(char *str);

#endif
