/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:09:33 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/19 15:09:46 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H
# include "libft.h"

typedef struct			s_int_node
{
	int					data;
	struct s_int_node	*next;
}						t_int_node;

typedef struct			s_stack
{
	t_int_node			*head;
	int					size;
}						t_stack;

t_int_node			*st_new_element(int n);
t_stack				*push(t_stack *st, t_int_node *p);
int					pop(t_stack *st);
int					peak(t_stack *st);
int					st_len(t_stack *st);

#endif