/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:49:35 by mchuang           #+#    #+#             */
/*   Updated: 2019/09/25 13:49:40 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_buf.h"

t_buf	*buf_init(void)
{
	t_buf	*to_ret;
	int		i;

	if (!(to_ret = (t_buf*)ft_memalloc(sizeof(t_buf))))
		return (NULL);
	i = 0;
	while (i <= BUF_SIZE)
		(to_ret->buf)[i++] = 0;
	to_ret->len = 0;
	to_ret->total = 0;
	return (to_ret);
}

void	buf_store_str(t_buf *buf, char *to_add)
{
	int		s_len;
	char	*cur;

	s_len = (int)ft_strlen(to_add);
	buf->total += s_len;
	if (s_len >= (BUF_SIZE - buf->len))
		buf_output_clear(buf);
	cur = to_add;
	while (s_len >= BUF_SIZE)
	{
		ft_strncpy(buf->buf + buf->len, cur, BUF_SIZE);
		buf->len = BUF_SIZE;
		buf_output_clear(buf);
		cur += BUF_SIZE;
		s_len -= BUF_SIZE;
	}
	ft_strncpy(buf->buf + buf->len, cur, s_len);
	buf->len += s_len;
}

void	buf_store_chr(t_buf *buf, unsigned char to_add)
{
	if (buf->len == BUF_SIZE)
		buf_output_clear(buf);
	(buf->buf)[buf->len] = to_add;
	buf->len++;
	buf->total++;
}

void	buf_output_clear(t_buf *buf)
{
	write(1, buf->buf, buf->len);
	ft_bzero(buf->buf, BUF_SIZE);
	buf->len = 0;
}

int		buf_del(t_buf *buf)
{
	int		to_ret;

	to_ret = buf->total;
	free(buf);
	return (to_ret);
}
