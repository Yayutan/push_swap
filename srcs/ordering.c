#include "push_swap.h"

static int		set_one_group_a(t_ps *ps, int i, int ord)
{
	int		gp;
	int		sym_put;

	gp = 0;
	while (gp < ps->max_symbols)
	{
		sym_put = 0;
		while (sym_put < ps->sym_p_pt && i >= 0 && i < ps->len)
		{
			ps->sorted[i]->group = (ord == 1) ? gp : (ps->max_symbols - 1 - gp);
			sym_put++;
			i++;
		}
		gp++;
	}
	return (i);
}

int		fill_to_a(t_ps *ps, int i, int layer, int ord)
{
	if (layer <= 1)
		i = set_one_group_a(ps, i, ord);
	else if (ord == 1)
	{
		i = fill_to_a(ps, i, layer - 1, -1);
		i = fill_to_a(ps, i, layer - 1, -1);
		i = fill_to_a(ps, i, layer - 1, -1);
		i = fill_to_a(ps, i, layer - 1, 1);
		i = fill_to_a(ps, i, layer - 1, 1);
	}
	else if (ord == -1)
	{
		i = fill_to_a(ps, i, layer - 1, -1);
		i = fill_to_a(ps, i, layer - 1, -1);
		i = fill_to_a(ps, i, layer - 1, 1);
		i = fill_to_a(ps, i, layer - 1, 1);
		i = fill_to_a(ps, i, layer - 1, 1);
	}
	return (i);
}

static int		set_one_group_b(t_ps *ps, int i, int ord)
{
	int		gp;
	int		sym_put;

	gp = 0;
	while (gp < ps->max_symbols)
	{
		sym_put = 0;
		while (sym_put < ps->sym_p_pt && i >= 0 && i < ps->len)
		{
			ps->sorted[i]->group = (ord == 1) ? gp : (ps->max_symbols - 1 - gp);
			sym_put++;
			i--;
		}
		gp++;
	}
	return (i);
}

int		fill_to_b(t_ps *ps, int i, int layer, int ord)
{
	if (layer <= 1)
		i = set_one_group_b(ps, i, ord);
	else if (ord == 1)
	{
		i = fill_to_b(ps, i, layer - 1, 1);
		i = fill_to_b(ps, i, layer - 1, 1);
		i = fill_to_b(ps, i, layer - 1, -1);
		i = fill_to_b(ps, i, layer - 1, -1);
		i = fill_to_b(ps, i, layer - 1, -1);
	}
	else if (ord == -1)
	{
		i = fill_to_b(ps, i, layer - 1, 1);
		i = fill_to_b(ps, i, layer - 1, 1);
		i = fill_to_b(ps, i, layer - 1, 1);
		i = fill_to_b(ps, i, layer - 1, -1);
		i = fill_to_b(ps, i, layer - 1, -1);
	}
	return (i);
}
