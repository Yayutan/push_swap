/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 21:39:32 by mchuang           #+#    #+#             */
/*   Updated: 2019/11/21 21:39:35 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_util.h"

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

int						*valid_int(char *str)
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
		if (!(to_ret = ft_memalloc(sizeof(int))))
			return (NULL);
		*to_ret = (int)content;
	}
	return (to_ret);
}

static void				print_helper(t_int_node *a, t_int_node *b, int c)
{
	char	*sa;
	char	*sb;
	int		wa;
	int		wb;

	sa = (a) ? ft_itoa(a->data) : ft_strnew(0);
	sb = (b) ? ft_itoa(b->data) : ft_strnew(0);
	wa = (11 - ft_strlen(sa)) / 2;
	wb = (14 - wa - ft_strlen(sa)) + ((11 - ft_strlen(sb)) / 2);
	if (c && a && a->red)
		ft_printf("%*s{RED}%s{CLEAR}", wa, "", sa);
	else
		ft_printf("%*s%s", wa, "", sa);
	if (c && b && b->red)
		ft_printf("%*s{RED}%s{CLEAR}\n", wb, "", sb);
	else
		ft_printf("%*s%s\n", wb, "", sb);
	if (a)
		a->red = 0;
	if (b)
		b->red = 0;
	free(sa);
	free(sb);
}

void					print_stack(char *ins, int c, t_stack *a, t_stack *b)
{
	t_int_node	*cur_a;
	t_int_node	*cur_b;

	ft_printf("Now executing ---> %s\n", ins);
	cur_a = (a) ? a->head : NULL;
	cur_b = (b) ? b->head : NULL;
	while (cur_a || cur_b)
	{
		print_helper(cur_a, cur_b, c);
		cur_a = (cur_a) ? cur_a->next : cur_a;
		cur_b = (cur_b) ? cur_b->next : cur_b;
	}
	ft_printf("-----------   -----------\n%6s%14s\n\n", "a", "b");
}

void					clean_str_arr(char **a)
{
	int		i;

	if (!a)
		return ;
	i = 0;
	while (a[i])
		free(a[i++]);
	free(a);
}
