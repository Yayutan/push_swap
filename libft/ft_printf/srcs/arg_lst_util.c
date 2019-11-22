/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_lst_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 18:33:52 by mchuang           #+#    #+#             */
/*   Updated: 2019/10/26 18:33:54 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg_list.h"

t_args	*new_arg(int i, char s)
{
	t_args	*to_ret;

	if (!(to_ret = (t_args*)ft_memalloc(sizeof(t_args))))
		ft_err_exit("Failed to allocate param list");
	to_ret->index = i;
	to_ret->size = s;
	to_ret->next = NULL;
	return (to_ret);
}

t_args	*put_between(t_args *pre, t_args *nxt, t_args *t)
{
	if (!pre)
	{
		t->next = nxt;
		return (t);
	}
	else
	{
		pre->next = t;
		t->next = nxt;
		return (pre);
	}
}

t_args	*insert_arg(t_args *lst, t_args *t)
{
	t_args	*cur;
	t_args	*pre;

	if (!lst || t->index < lst->index)
		return (put_between(NULL, lst, t));
	pre = NULL;
	cur = lst;
	while (cur && cur->index < t->index)
	{
		pre = cur;
		cur = cur->next;
	}
	if (!cur)
		pre->next = t;
	else if (t->index == cur->index)
	{
		cur->size = t->size;
		free(t);
	}
	else if (t->index < cur->index && t->index > pre->index)
		pre = put_between(pre, cur, t);
	return (lst);
}

t_args	*arg_lst_at(t_args *lst, int pos)
{
	t_args	*cur;

	if (!lst || pos == 0)
		return (NULL);
	else if (pos == 1)
		return (lst);
	else
	{
		cur = lst;
		while (cur)
		{
			if (pos == 1)
				return (cur);
			pos--;
			cur = cur->next;
		}
		return (NULL);
	}
}

void	arg_lst_del(t_args *lst)
{
	t_args	*cur;
	t_args	*nxt;

	cur = lst;
	while (cur)
	{
		nxt = cur->next;
		free(cur);
		cur = nxt;
	}
}
