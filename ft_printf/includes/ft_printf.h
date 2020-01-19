/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchuang <mchuang@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:17:22 by mchuang           #+#    #+#             */
/*   Updated: 2019/09/24 16:19:14 by mchuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include "ft_buf.h"
# include "arb_pre.h"
# include "arg_list.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <time.h>

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAG "\033[0;35m"
# define CYAN "\033[0;36m"
# define CLEAR "\033[0m"

typedef struct		s_spec
{
	int				param;
	int				flags[6];
	int				width;
	int				precision;
	int				len;
	char			specifier;
	int				valid;
	char			sign[2];
	char			pref[3];
	t_args			*arg;
	va_list			param_lst;
	va_list			orig;
}					t_spec;

union				u_double
{
	double			dbl;
	char			data[sizeof(double)];
};

union				u_ldouble
{
	long double		ldbl;
	char			data[sizeof(long double)];
};

union				u_argument
{
	unsigned char	uc;
	char			*str;
	struct tm		*ts;
	double			d;
	long double		ld;
	short			sh;
	int				i;
	long int		li;
	long long int	lli;
};

int					ft_printf(const char *format, ...);
t_args				*set_args_lst(char *format);
void				process_output(char *ft, t_buf *b, t_args *al, va_list or);
int					add_arg_info(char *ft, int i, t_args **arg, int *nxt_arg);
void				clear_param(t_spec *sp);
void				del_spec(t_spec *sp);
int					star_param(int *st, char *ft, t_spec *sp, t_args *al);
int					dot_param(int *pc, char *ft, t_spec *sp, t_args *al);
int					not_num_param(t_spec *sp, char *ft, int i);
int					num_param(t_spec *sp, char *ft, int j);
int					change_color(char *ft, int i, t_buf *buf);
char				*i_f(t_spec *sp, char *format, int *i);
char				*d_p_f(t_buf *b, t_spec *sp, t_args *al);
union u_argument	next_arg(t_args *arg, va_list param);
union u_argument	nth_arg_orig(t_args *arg, int n, va_list orig);
union u_argument	nth_arg_sp(t_args *arg, int n, va_list sp);
char				*initial_s(t_spec *sp, union u_argument u_arg);
char				*initial_c(t_spec *sp, t_buf *buf, union u_argument u_arg);
char				*initial_diouxb(t_spec *sp, union u_argument u_arg);
char				*initial_p(t_spec *sp, union u_argument u_arg);
char				*initial_k(t_buf *buf, union u_argument u_arg);
char				*initial_feg(t_spec *sp, union u_argument u_arg);
char				*initial_f(t_spec *sp, union u_argument u_arg);
char				*initial_e(t_spec *sp, union u_argument u_arg);
char				*initial_g(t_spec *sp, union u_argument u_arg);
int					setup_basic(t_spec *sp, union u_argument u_arg, char **b);
int					get_d_exp(union u_double u_d);
int					get_ld_exp(union u_ldouble u_ld);
int					get_d_mantissa(union u_double u_d, char *m);
int					get_ld_mantissa(union u_ldouble u_d, char *m);
int					shift_mantissa(char *res, int e);
int					udtoa_basic(union u_double u_d, char **str);
int					uldtoa_basic(union u_ldouble u_ld, char **str);
int					calc_exp(char *dec, int p);
char				*form_dec(char *dec, int exp, int hash, int pre);
char				*append_exp(char *dec, int exp);
char				*form_final(char *man, int dec, int pre, int hash);
void				clear_digits(char *n, int pos);
char				*finalize(t_spec *sp, char *str);
#endif
