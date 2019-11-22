/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 16:37:54 by mchuang           #+#    #+#             */
/*   Updated: 2019/10/25 16:37:55 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARG_LIST_H
# define ARG_LIST_H
# include <stdarg.h>
# include <stdlib.h>
# include "libft.h"

typedef struct			s_args
{
	int					index;
	char				size;
	struct s_args		*next;
}						t_args;

t_args					*new_arg(int i, char s);
t_args					*insert_arg(t_args *lst, t_args *t);
t_args					*arg_lst_at(t_args *lst, int i);
void					arg_lst_del(t_args *lst);

#endif
