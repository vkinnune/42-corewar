/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 05:42:47 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/19 02:28:47 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	put_c(va_list ap)
{
	char		c;
	int			length;

	length = 1;
	if (g_order.conv == 'c')
	{
		c = va_arg(ap, int);
		bundling_bundler(&length, NULL);
	}
	else
	{
		set_percent_sign();
		c = '%';
		bundling_bundler(&length, &hash_pos_spc);
	}
	g_p_str.s[g_p_str.i++] = c;
	return (length);
}

int	put_s(va_list ap)
{
	char		*s;
	int			length;
	int			str_len;

	s = va_arg(ap, char *);
	if (s == NULL)
		s = "(null)";
	str_len = ft_strlen(s);
	if (g_order.prec > 0 && g_order.prec < str_len)
		length = g_order.prec;
	else if (g_order.prec == -1)
		length = 0;
	else
		length = str_len;
	bundling_bundler(&length, NULL);
	if (g_order.mfw == 0 && g_order.prec == -1)
		return (0);
	else if (g_order.mfw != 0 && g_order.prec == -1)
		put_flag(g_order.mfw - g_order.num_of_padding, ' ');
	else if (g_order.prec > 0)
		cpy_to_g_str(s, ft_smallernum(g_order.prec, str_len));
	else
		cpy_to_g_str(s, str_len);
	return (length);
}

int	put_d(va_list ap)
{
	long long int	n;
	int				length;
	int				long_min_val;

	length = 0;
	n = va_arg(ap, long long int);
	int_converter(NULL, &n);
	long_min_val = check_value(0, &n);
	length += ft_diglen(n) - long_min_val;
	bundling_bundler(&length, &hash_pos_spc);
	if (n == (long long int)-9223372036854775808u)
	{
		cpy_to_g_str("9223372036854775808", 19);
		return (length);
	}
	if (g_order.prec == -1 && n == 0)
	{
		if (g_order.mfw > 1)
			g_p_str.s[g_p_str.i++] = ' ';
		else
			return (length - 1);
	}
	else
		cpy_to_g_str(ft_itoa(n), ft_diglen(n));
	return (length);
}

int	put_f(va_list ap)
{
	long double	f;
	int			length;

	set_f_values();
	length = 0;
	if (g_order.flag[0] == 'L')
		f = va_arg(ap, long double);
	else
		f = va_arg(ap, double);
	check_f_value(&f);
	length += ft_diglen(f) + g_order.prec
		+ (g_order.prec != 0);
	bundling_bundler(&length, &hash_pos_spc);
	length += ft_putfloat_fd(f, g_order.prec, g_order.fd);
	if (!g_order.prec && g_order.hash)
		g_p_str.s[g_p_str.i++] = '.';
	return (length);
}

int	put_pbouxx(va_list ap)
{
	int						length;
	unsigned long long int	u;

	set_pbouxx_values();
	length = 0;
	if (g_order.conv == 'p')
		u = (intptr_t)va_arg(ap, void *);
	else
		u = va_arg(ap, unsigned long long int);
	if (g_order.conv != 'p')
		int_converter(&u, 0);
	length += check_value(u, 0) + ft_udiglen(u, g_order.base);
	bundling_bundler(&length, &hash_pos_spc);
	if (u == 0 && g_order.prec == -1
		&& ((g_order.conv != 'p' && g_order.conv != 'o')
			|| (g_order.conv == 'o' && g_order.hash == 0)))
	{
		if (g_order.mfw)
			g_p_str.s[g_p_str.i++] = ' ';
		else
			return (length - 1);
	}
	else if (!(g_order.conv == 'p' && g_order.prec == -1))
		printf_d2base(u, g_order.base, g_order.conv, 0);
	return (length - (g_order.conv == 'p' && g_order.prec == -1));
}
