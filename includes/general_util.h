/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_util.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 21:39:22 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/21 21:39:24 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_UTIL_H
# define GENERAL_UTIL_H
# include "../ft_printf/includes/ft_printf.h"
# include "../libft/stack.h"
# include "../libft/queue.h"

void		print_stack(char *info, int c, t_stack *st_a, t_stack *st_b);
int			*valid_int(char *str);
void		clean_str_arr(char **a);
#endif
