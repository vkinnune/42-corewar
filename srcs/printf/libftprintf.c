/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 10:49:10 by qnguyen           #+#    #+#             */
/*   Updated: 2022/06/10 16:34:58 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_order		g_order;
t_function	*g_function_arr[5] = {put_c, put_s, put_d, put_f, put_pbouxx};

int	print_error(char *og_fmt, char *fmt)
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

int	take_subway_order(char **fmt, va_list ap)
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
		i = g_function_arr[g_order.func_idx](ap);
		if (g_order.neg)
			put_flag(g_order.num_of_padding, ' ', g_order.fd);
		return (i);
	}
	return (print_error(og_fmt, *fmt));
}

int	grouping_grouper(char **fmt, va_list ap,
			char default_color[5], int *fd)
{
	int	char_printed;

	if (**fmt == '%')
	{
		initialize_order(*fd);
		char_printed = take_subway_order(fmt, ap);
		if (g_order.color)
			write(*fd, default_color, 5);
	}
	else if (**fmt == '$')
	{
		extra_functionality(fmt, default_color, fd, ap);
		char_printed = 0;
	}
	else
		char_printed = write(*fd, *fmt, 1);
	return (char_printed);
}

int	ft_printf(const char *fmt, ...)
{
	char	default_color[6];
	int		char_printed;
	va_list	ap;
	int		fd;

	fd = 1;
	ft_strcpy(default_color, "\x1b[0m");
	va_start(ap, fmt);
	char_printed = 0;
	while (*fmt)
	{
		char_printed += grouping_grouper((char **)&fmt, ap,
				default_color, &fd);
		if (*fmt)
			fmt++;
	}
	va_end(ap);
	return (char_printed);
}
