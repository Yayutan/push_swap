
#include "push_swap.h"

int		exponential(int b, int p)
{
	int		i;
	int		res;

	i = 0;
	res = 1;
	while (i < p)
	{
		res *= b;
		i++;
	}
	return (res);
}

int		log_m_ceil(int n, int m)
{
	int		log;
	int		cur;

	log = 0;
	cur = 1;
	while (cur < n)
	{
		cur *= m;
		log++;
	}
	return (log);
}



static void		update_index(t_ps *ps, int end_b)
{
	int		i;
	int		pt;
	int		mid;

	mid = ps->n_parts / 2 + (ps->n_parts % 2);
	i = (end_b) ? (ps->len - 1) : 0;
	pt = 0;
	while (pt < mid)
	{		
		if (end_b)
			i = fill_to_b(ps, i, ps->layer , 1);
		else
			i = fill_to_a(ps, i, ps->layer, -1);
		pt++;
	}
	while (pt < ps->n_parts)
	{		
		if (end_b)
			i = fill_to_b(ps, i, ps->layer, -1);
		else
			i = fill_to_a(ps, i, ps->layer, 1);
		pt++;
	}
}

static void		put_two_groups(t_ps *ps, int a_to_b, int top_layer, int bot_layer)
{
	t_stack		*from;
	int			len;
	int			i;

	from = (a_to_b) ? ps->a : ps->b;
	len = from->size;
	i = 0;
	while (i < len)
	{
		if (from->head->group == top_layer)
		{
			if (a_to_b)
				pt_instruction(ps->a, ps->b, "pb");
			else
				pt_instruction(ps->a, ps->b, "pa");
		}
		else if (from->head->group == bot_layer)
		{
			if (a_to_b)
			{
				pt_instruction(ps->a, ps->b, "pb");
				pt_instruction(ps->a, ps->b, "rb");
			}
			else
			{
				pt_instruction(ps->a, ps->b, "pa");
				pt_instruction(ps->a, ps->b, "ra");
			}
		}
		else
		{
			if (a_to_b)
				pt_instruction(ps->a, ps->b, "ra");
			else
				pt_instruction(ps->a, ps->b, "rb");
		}
		i++;
	}
}

static void		put_by_index(t_ps *ps, int end_b)
{
	int		top;
	int		bot;
	int		iter;

	top = (ps->max_symbols - 1) / 2;
	bot = top + 1;
	iter = (ps->max_symbols + 1) / 2;
	while (iter > 0)
	{
		put_two_groups(ps, end_b, top, bot);
		top--;
		bot++;
		iter--;
	}	
}

// need to handle small numbers
static void		radix_sort(t_ps *ps)
{
	int		num_iter;
	int		out_iter;

	num_iter = log_m_ceil(ps->len, ps->max_symbols);
	out_iter = 1;
	ps->layer = num_iter - 1;
	while (out_iter <= num_iter)
	{
		if (out_iter < num_iter)
			update_index(ps, (num_iter % 2));
		else
			(num_iter % 2) ? final_ord_rev(ps) : final_ord(ps);
		put_by_index(ps, (out_iter % 2));
		out_iter++;
		ps->sym_p_pt *= ps->max_symbols;
	}
	if (ps->a->size == 0)
	{
		num_iter = ps->b->size;
		while (num_iter > 0)
		{
			pt_instruction(ps->a, ps->b, "pa");
			num_iter--;
		}
	}
}

static void		sort_small(t_ps *ps)
{
	ps->len = 0;
}

void			sort(t_ps *ps)
{
	double 	four_steps;
	double 	five_steps;
	int		n;

	n = ps->a->size;
	ps->len = n;
	four_steps = 2.0 * n * log_m_ceil(n, 4) +  n * (log_m_ceil(n, 4) % 2);
	five_steps = 2.2 * n * log_m_ceil(n, 5) +  n * (log_m_ceil(n, 5) % 2);
	if (four_steps < five_steps)
		ps->max_symbols = 4;
	else
		ps->max_symbols = 5;
	ps->sym_p_pt = 1;
	n = exponential(ps->max_symbols, log_m_ceil(ps->len, ps->max_symbols));
	if (ps->len == n)
		ps->n_parts = ps->max_symbols;
	else
	{
		n /= ps->max_symbols;
		ps->n_parts = ps->len / n + (ps->len % n != 0);
	}
	(ps->len <= 5) ? sort_small(ps) : radix_sort(ps);
}
