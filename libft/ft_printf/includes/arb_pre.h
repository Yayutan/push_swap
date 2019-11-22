/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arb_pre.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 01:47:16 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/08 01:47:19 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARB_PRE_H
# define ARB_PRE_H
# include "libft.h"
# define LEN 20481
# define DEC 4097
# define WH 16384

void	add(char *n1, const char *n2);
void	sub(char *n1, const char *n2);
void	basic_mult(char *n1, char *n2);
void	mult(char *n1, char *n2);
void	divi(char *n1, const char *n2);
void	clear_str(char *n, int length);
int		basic_divi(char *n1, char *n2, int leng);
void	increment(char *n1, int index);
int		cmp_size(char *n1, char *n2, int leng);
#endif
