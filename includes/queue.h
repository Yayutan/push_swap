/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:12:47 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/19 15:12:57 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H
# include "libft.h"

typedef struct		s_str_node
{
	char				*data;
	struct s_str_node	*next;
}					t_str_node;

typedef struct			s_queue
{
	t_str_node			*head;
	t_str_node			*tail;
	int					size;
}						t_queue;

t_str_node			*q_new_element(char *n);
t_queue				*enqueue(t_queue *q, t_str_node *p);
char				*dequeue(t_queue *q);
char				*front(t_queue *q);
int					len(t_queue *q);


#endif