/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 19:03:59 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/19 19:04:37 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "checker.h"

static long long int	atolli(char *s)
{
	long long int	to_ret;
	int				i;
	int				neg;

	neg = (s[0] == '-');
	to_ret = 0;
	i = (ft_strchr("+-", s[0])) ? 1 : 0;
	while (s[i] && i <= 13)
	{
		to_ret = to_ret * 10 + s[i] - '0';
		i++;
	}
	to_ret *= (neg) ? -1 : 1;
	return (to_ret);
}

int					*valid_int(char *str)
{
	int				*to_ret;
	long long int	content;
	int				i;

	if (!str || !*str)
		return (NULL);
	i = (ft_strchr("+-", str[0])) ? 1 : 0;
	if (i == 1 && !(str[i]))
		return (NULL);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (NULL);
		i++;
	}
	content = atolli(str);
	if (content > INT_MAX || content < INT_MIN)
		return (NULL);
	else
	{
		if (!(to_ret = ft_memalloc(sizeof(int*))))
			return (NULL);
		*to_ret = (int)content;
	}
	return (to_ret);
}
