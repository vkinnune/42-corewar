/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 16:19:29 by qnguyen           #+#    #+#             */
/*   Updated: 2022/05/31 14:04:32 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	put_flag(int ammount, char c, int fd)
{
	while (ammount-- > 0)
		write(fd, &c, 1);
}

void	a_wild_mfw_appeared(va_list ap, char mfw_prec)
{
	int	n;

	n = va_arg(ap, int);
	if (n < 0)
	{
		if (g_order.mfw || mfw_prec == 'p')
			return ;
		n = -n;
		g_order.neg = 1;
	}
	if (mfw_prec == 'm')
		g_order.mfw = n;
	else if (mfw_prec == 'p')
		g_order.prec = -(!n) | n;
}

void	mfw_prec_assigner(char **fmt, va_list ap)
{
	if (**fmt == '.')
	{
		(*fmt)++;
		if (**fmt == '*')
		{
			a_wild_mfw_appeared(ap, 'p');
			(*fmt)++;
			return ;
		}
		if (ft_atoi(*fmt) == 0)
			g_order.prec = -1;
		else
			g_order.prec = ft_atoi(*fmt);
	}
	else
		g_order.mfw = ft_atoi(*fmt);
}

/* void	printf_d(int *fd, va_list ap, char fmt)
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
} */

void	extra_functionality(char **fmt, char default_color[6], int *fd,
			va_list ap)
{
	char	*color;

	color = NULL;
	(*fmt)++;
	if (*(*fmt) == 'r')
		color = "\x1B[31m";
	else if (**fmt == 'g')
		color = "\x1B[32m";
	else if (**fmt == 'b')
		color = "\x1B[34m";
	else if (**fmt == 'd')
		color = "\x1B[0m";
	else if (**fmt == '0')
		*fd = va_arg(ap, int);
	else
	{
		write(*fd, "$", 1);
		if (**fmt == '$')
			(*fmt)++;
		write(*fd, *fmt, 1);
	}
	if (color)
		write(*fd, color, 5);
	if (default_color && color)
		ft_strcpy(default_color, color);
}
