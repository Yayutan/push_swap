/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:48:20 by mchuang           #+#    #+#             */
/*   Updated: 2019/09/25 13:48:31 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUF_H
# define FT_BUF_H
# include <unistd.h>
# include "libft.h"
# define BUF_SIZE 1024

typedef struct	s_buf
{
	char		buf[BUF_SIZE + 1];
	int			len;
	int			total;
}				t_buf;

t_buf			*buf_init(void);
void			buf_store_str(t_buf *buf, char *to_add);
void			buf_store_chr(t_buf *buf, unsigned char to_add);
void			buf_output_clear(t_buf *buf);
int				buf_del(t_buf *buf);
#endif
