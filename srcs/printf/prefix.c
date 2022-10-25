/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 11:17:10 by qnguyen           #+#    #+#             */
/*   Updated: 2022/04/13 14:18:52 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	helping_helper(char fmt)
{
	g_order.space += (fmt == ' ');
	g_order.hash += (fmt == '#');
	g_order.zero += (fmt == '0');
	g_order.neg += (fmt == '-');
	g_order.pos += (fmt == '+');
}

void	check_prefix(char **fmt, va_list ap)
{
	while (**fmt == ' ' || **fmt == '#' || **fmt == '-' || **fmt == '+'
		|| **fmt == '.' || **fmt == '$' || **fmt == '*' || ft_isdigit(**fmt))
	{
		if (g_order.mfw == 0 && g_order.prec == 0)
			helping_helper(**fmt);
		if ((**fmt >= '1' && **fmt <= '9') || **fmt == '.')
		{
			mfw_prec_assigner(fmt, ap);
			while (ft_isdigit(**fmt) || **fmt == '-' || **fmt == '+')
				(*fmt)++;
			if (**fmt != '.')
				return ;
			(*fmt)--;
		}
		else if (**fmt == '$')
		{
			g_order.color = 1;
			extra_functionality(fmt, 0, &g_order.fd, ap);
		}
		else if (**fmt == '*')
			a_wild_mfw_appeared(ap, 'm');
		(*fmt)++;
	}
}

void	check_flag(char **fmt)
{
	if (**fmt == 'h' || **fmt == 'l' || **fmt == 'L')
	{
		if ((*fmt)[1] == **fmt)
		{
			g_order.flag[1] = **fmt;
			(*fmt)++;
		}
		g_order.flag[0] = **fmt;
		(*fmt)++;
	}
}

void	check_conv(char **fmt)
{
	char	conv[13];
	int		i;

	if (**fmt == 'i')
	{
		g_order.conv = 'd';
		g_order.func_idx = 2;
		return ;
	}
	ft_strcpy(conv, "csdfpbouxX %\0");
	i = -1;
	while (conv[++i])
	{
		if (**fmt == conv[i])
		{
			g_order.conv = **fmt;
			g_order.func_idx = i;
		}
	}
	if (**fmt == '%')
		g_order.func_idx = 0;
	if (g_order.func_idx > 4)
		g_order.func_idx = 4;
}
