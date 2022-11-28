/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 16:19:29 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/19 05:30:54 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	put_flag(int ammount, char c)
{
	int	i;

	i = 0;
	while (i < ammount)
	{
		g_p_str.s[g_p_str.i++] = c;
		i++;
	}
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
