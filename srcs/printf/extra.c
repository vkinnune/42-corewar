/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 04:39:51 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/19 05:23:53 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	print_fd(int *fd, va_list ap, char fmt)
{
	char	*s;

	if (fmt == '0')
		*fd = va_arg(ap, int);
	else
	{
		s = va_arg(ap, char *);
		*fd = open(s, O_WRONLY);
	}
	if (*fd == -1)
		write(2, "error: cannot open file\n", 24);
}

static void	print_double_dollar(char **fmt)
{
	g_p_str.s[g_p_str.i++] = '$';
	if (**fmt == '$')
		(*fmt)++;
	g_p_str.s[g_p_str.i++] = **fmt;
}

static void	set_color(char **color, int default_mod)
{
	if (color)
		cpy_to_g_str(*color, ft_strlen(*color));
	if (default_mod && color)
		ft_strcpy(g_printf_default_color, *color);
}

void	extra_functionality(char **fmt, va_list ap, int *fd, int default_mod)
{
	char	*color;

	color = NULL;
	(*fmt)++;
	if (**fmt == 'r')
		color = "\x1B[31m";
	else if (**fmt == 'g')
		color = "\x1B[32m";
	else if (**fmt == 'b')
		color = "\x1B[34m";
	else if (**fmt == 'd')
		color = "\x1B[0m";
	else if (**fmt == '0' || **fmt == '1')
		print_fd(fd, ap, **fmt);
	else
		print_double_dollar(fmt);
	set_color(&color, default_mod);
}
