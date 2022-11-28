/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 10:49:12 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/19 05:15:48 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include <stdarg.h>
# include "libft.h"
# include <fcntl.h>

# define STRING_SIZE 1000

typedef struct s_order
{
	int		space;
	int		hash;
	int		zero;
	int		neg;
	int		pos;
	int		base;
	int		negative_num;
	int		color;
	int		mfw;
	int		prec;
	int		num_of_padding;
	int		num_of_zeros;
	int		func_idx;
	int		fd;
	char	conv;
	char	flag[2];
}				t_order;

typedef struct s_printf_string
{
	int		i;
	char	s[STRING_SIZE];
}				t_printf_string;

typedef int				t_printf_funcs(va_list ap);
extern t_order			g_order;
extern t_printf_string	g_p_str;
extern char				g_printf_default_color[5];

//libftprintf.c
int		ft_printf(const char *format, ...);

//prefix.c
void	helping_helper(char fmt);
void	check_prefix(char **fmt, va_list ap);
void	check_flag(char **fmt);
void	check_conv(char **fmt);

//init.c
void	printf_init(int *fd, int *char_count);
void	initialize_order(int fd);

//utilities.c
void	int_converter(unsigned long long int *u, long long *n);
void	bundling_bundler(int *length, int (*f)(void));
int		check_value(unsigned long long u, long long int *n);
void	check_f_value(long double *f);
void	cpy_to_g_str(char *src, int amount);

//utilities_2.c
void	put_flag(int ammount, char c);
void	a_wild_mfw_appeared(va_list ap, char m_p);
void	mfw_prec_assigner(char **fmt, va_list ap);

//extra.c
void	extra_functionality(char **fmt, va_list ap, int *fd, int default_mod);

//printer.c
int		put_c(va_list ap);
int		put_s(va_list ap);
int		put_d(va_list ap);
int		put_f(va_list ap);
int		put_pbouxx(va_list ap);

//printf_d2base.c
void	printf_d2base(unsigned long long n, int base, char x, int i);

//print_float.c
void	cpy_float(long double lift, int prec);

//flags_handler.c
int		hash_pos_spc(void);
int		cal_zero(int length);
void	cal_padding(int length);
int		mfw(int length, int (*f)(void));

//conversion_prefix_adapter.c
void	conversion_adapter(void);
void	set_pbouxx_values(void);
void	set_percent_sign(void);
void	set_f_values(void);

#endif
