/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 10:49:10 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/19 05:29:42 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_order			g_order;
t_printf_funcs	*g_print_funcs[5] = {put_c, put_s, put_d, put_f, put_pbouxx};
t_printf_string	g_p_str;
char			g_printf_default_color[5];

static int	print_error(char *og_fmt, char *fmt)
{
	int	i;

	i = 0;
	while (og_fmt <= fmt && *og_fmt)
	{
		if (*og_fmt == '*')
			ft_putnbr_fd(g_order.mfw, g_order.fd);
		else if (*og_fmt != '0')
			write(g_order.fd, og_fmt, 1);
		if (*og_fmt == '.' && !ft_isdigit(og_fmt[1]))
			write(g_order.fd, "0", 1);
		i++;
		og_fmt++;
	}
	return (i);
}

static int	take_subway_order(char **fmt, va_list ap)
{
	char	*og_fmt;
	int		i;

	og_fmt = *fmt;
	(*fmt)++;
	if (!**fmt)
		return (0);
	check_prefix(fmt, ap);
	check_flag(fmt);
	check_conv(fmt);
	conversion_adapter();
	if (g_order.conv)
	{
		i = g_print_funcs[g_order.func_idx](ap);
		if (g_order.neg)
			put_flag(g_order.num_of_padding, ' ');
		return (i);
	}
	return (print_error(og_fmt, *fmt));
}

static int	convert(char **fmt, va_list ap, int *fd)
{
	int	char_printed;

	initialize_order(*fd);
	char_printed = take_subway_order(fmt, ap);
	if (g_order.color)
		cpy_to_g_str(g_printf_default_color, ft_strlen(g_printf_default_color));
	return (char_printed);
}

int	ft_printf(const char *fmt, ...)
{
	int		char_printed;
	int		fd;
	va_list	ap;

	printf_init(&fd, &char_printed);
	va_start(ap, fmt);
	while (*fmt)
	{
		if (*fmt == '%')
			char_printed += convert((char **)&fmt, ap, &fd);
		else if (*fmt == '$')
			extra_functionality((char **)&fmt, ap, &fd, 1);
		else
		{
			g_p_str.s[g_p_str.i++] = *fmt;
			char_printed++;
		}
		if (*fmt)
			fmt++;
	}
	va_end(ap);
	write(fd, g_p_str.s, g_p_str.i);
	return (char_printed);
}
