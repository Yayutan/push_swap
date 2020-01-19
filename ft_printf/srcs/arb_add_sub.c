/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arb_add_sub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 01:48:17 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/08 01:48:18 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arb_pre.h"

void	increment(char *n1, int index)
{
	if (index >= 0)
	{
		if (n1[index] == '.')
			increment(n1, index - 1);
		n1[index] = ((n1[index] - '0' + 1) % 10) + '0';
		if (n1[index] == '0')
			increment(n1, index - 1);
	}
}

void	add(char *n1, const char *n2)
{
	int	i;
	int	j;
	int	p;

	i = ft_strlen(n1) - 1;
	j = ft_strlen(n2) - 1;
	p = 0;
	while (i >= 0)
	{
		n1[i] += p / 10;
		p = (j >= 0) ? (n1[i] + n2[j] - '0' * 2) : (n1[i] - '0');
		n1[i] = p % 10 + '0';
		i--;
		j--;
	}
}

void	sub(char *n1, const char *n2)
{
	int	i;
	int	j;
	int	p;

	i = ft_strlen(n1) - 1;
	j = ft_strlen(n2) - 1;
	p = 10;
	while (i >= 0)
	{
		n1[i] -= (p < 10);
		p = (j >= 0) ? (n1[i] - n2[j] + 10) : (n1[i] - '0');
		n1[i] = p % 10 + '0';
		i--;
		j--;
	}
}

void	clear_str(char *n, int length)
{
	int	i;

	i = 0;
	while (i < length)
		n[i++] = '0';
	n[i] = '\0';
}
