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
# include <limits.h>

int		*valid_int(char *str);
void	print_stack(t_stack *st_a, t_stack *st_b);
void	print_queue(char *name, t_queue *q);
void	setup_structs(t_stack **a, t_stack **b, t_queue **ins);
void	clean_up_structs(t_stack *a, t_stack *b, t_queue *ins);

#endif