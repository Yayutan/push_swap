#include "push_swap.h"


void	final_ord(t_ps *ps)
{
	int		pt;
	int		gp;
	int		n_sym;
	int		i;

	pt = 0;
	if (ps->n_parts == 2)
		gp = (ps->max_symbols - 1) / 2;
	else if (ps->n_parts < ps->max_symbols)
		gp = (ps->max_symbols - 3) / 2;
	else
		gp = 0;
	i = 0;
	while (pt < ps->n_parts)
	{
		n_sym = 0;
		while (n_sym < ps->sym_p_pt && i >= 0 && i < ps->len)
		{
			ps->sorted[i++]->group = gp;
			n_sym++;
		}
		gp++;
		pt++;
	}
}



void	final_ord_rev(t_ps *ps)
{
	int		pt;
	int		gp;
	int		n_sym;
	int		i;

	pt = 0;
	if (ps->n_parts == 2)
		gp = (ps->max_symbols - 1) / 2;
	else if (ps->n_parts < ps->max_symbols)
		gp = (ps->max_symbols - 3) / 2;
	else
		gp = 0;
	i = ps->len - 1;
	while (pt < ps->n_parts)
	{
		n_sym = 0;
		while (n_sym < ps->n_parts && i >= 0 && i < ps->len)
		{
			ps->sorted[i--]->group = gp;
			n_sym++;
		}
		gp++;
		pt++;
	}
}