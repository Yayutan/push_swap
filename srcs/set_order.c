# include "push_swap.h"

// GETTER
static int		get_gp_4(char *layer, int gp_size, int index)
{
	char	cur_ord;
	int		gp;

	cur_ord = layer[index / gp_size];
	gp = (index / (gp_size / 4)) % 4;
	if (cur_ord == '0')
		gp = 3 - gp;
	return (gp);
}

static int		get_gp_5(char *layer, int gp_size, int last, int index)
{
	char	cur_ord;
	int		gp;

	cur_ord = layer[index / gp_size];
	gp = (index / (gp_size / 5)) % 5;
	if (last)
		return (gp + 1);
	if (cur_ord == '0')
		gp = 4 - gp;
	return (gp);
}

void	set_gp_stack(t_ps *ps, int to_b, int last)
{
	t_int_node *cur;
	int			index;

	cur = (ps->a->size) ? ps->a->head : ps->b->head;
	while (cur)
	{
		// if (last)
		// 	index = cur->index;
		// else
		index = (to_b) ? ps->len - 1 - cur->index : cur->index;
		// index = cur->index;
		if (ps->max_symbols == 5)
			cur->group = get_gp_5(ps->order[0], ps->sym_p_pt * 5, last, index);
		else
			cur->group = get_gp_4(ps->order[0], ps->sym_p_pt * 4, index);
		cur = cur->next;
	}
}


// SETTER

char	pat_4[4][4] = {"0011", "0011", "1100", "1100"};
char	pat_5[4][5] = {"00111", "00011", "11000", "11100"};
char	*pat[2][4]  = {{"0011", "0011", "1100", "1100"}, {"00111", "00011", "11000", "11100"}};

// # include <unistd.h>
// void	print_order_tree(char **order, int layers, int max_sym)
// {
// 	char	space = ' ';
// 	char	n_l = '\n';
// 	for (int i = 0; i < layers; i++)
// 	{
// 		for (int j = 0; order[i][j] != '\0'; j+= max_sym)
// 		{
// 			write(1, order[i] + j, max_sym);
// 			write(1, &space, 1);
// 		}
// 		write(1, &n_l, 1);
// 	}
// }

// try to generalize later
void	set_order_5(char **order, int layers, int max_sym)
{
	int		i;
	int		j;
	int		num_elements;

	// first figure out first layer
	order[layers - 1] = ft_strnew(max_sym);
	ft_strncpy(order[layers - 1], ((layers % 2) ? pat_5[0] : pat_5[2]), max_sym);
	i = layers - 2;
	num_elements = max_sym * max_sym;
	while (i >= 0)
	{
		order[i] = ft_strnew(num_elements);
		j = 0;
		while ((j < num_elements))
		{
			if (i % 2 == 0) // start with 0
			{
				if (order[i + 1][j / max_sym] == '0')
					ft_strncpy((*(order + i) + j), pat_5[1], max_sym); // 00011
				else
					ft_strncpy((*(order + i) + j), pat_5[0], max_sym); // 00111
			}
			else
			{
				if (order[i + 1][j / max_sym] == '0')
					ft_strncpy((*(order + i) + j), pat_5[2], max_sym); // 11000
				else
					ft_strncpy((*(order + i) + j), pat_5[3], max_sym); // 11100
			}
			j += max_sym;
		}
		i--;
		num_elements *= max_sym;
	}
}