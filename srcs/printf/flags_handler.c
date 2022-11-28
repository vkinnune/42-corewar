/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:42:06 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/19 01:59:13 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	do_bpxx(void)
{
	if (g_order.conv == 'b')
		cpy_to_g_str("0b", 2);
	else if (g_order.conv == 'X')
		cpy_to_g_str("0X", 2);
	else if (g_order.conv == 'x' || g_order.conv == 'p')
		cpy_to_g_str("0x", 2);
	return (2);
}

int	hash_pos_spc(void)
{
	if (g_order.hash > 0)
	{
		if (g_order.conv == 'b' || g_order.conv == 'X'
			|| g_order.conv == 'x' || g_order.conv == 'p')
			return (do_bpxx());
		if (g_order.conv == 'o')
			g_p_str.s[g_p_str.i++] = '0';
		return (1);
	}
	if (g_order.conv == 'd' || g_order.conv == 'f')
	{
		if (g_order.pos)
			g_p_str.s[g_p_str.i++] = '+';
		else if (g_order.space)
			g_p_str.s[g_p_str.i++] = ' ';
		return ((g_order.pos || g_order.space)
			* (g_order.conv == 'd' || g_order.conv == 'f'));
	}
	return (0);
}

int	cal_zero(int length)
{
	int	zero;

	if (g_order.num_of_zeros != 0)
		return (0);
	zero = g_order.mfw - (g_order.pos || g_order.space)
		- length - g_order.negative_num;
	if (!g_order.prec)
	{
		if (g_order.hash == 1 && g_order.conv != 'o')
			zero -= 2;
	}
	else
	{
		if (g_order.mfw > g_order.prec && g_order.conv != 'f')
				zero = g_order.mfw - length;
		else if (g_order.mfw <= g_order.prec)
			zero = g_order.prec - length;
	}
	g_order.num_of_zeros = (zero > 0) * zero;
	return (g_order.num_of_zeros);
}

void	cal_padding(int length)
{
	int	padding;

	padding = 0;
	padding = g_order.mfw - (g_order.pos || g_order.space)
		- length - g_order.negative_num;
	if (g_order.prec > length && g_order.conv != 's')
		padding -= g_order.prec - length;
	if (g_order.hash == 1 && (g_order.conv == 'o' ))
		padding -= 1;
	else if (g_order.hash == 1)
		padding -= 2;
	g_order.num_of_padding = (padding > 0) * padding;
}

int	mfw(int length, int (*f)(void))
{
	int	i;

	i = 0;
	if (length < g_order.mfw || length < g_order.prec)
	{
		if ((g_order.zero || g_order.mfw < g_order.prec)
			&& g_order.conv != 's' && g_order.conv != 'c')
		{
			if (f)
				i += f();
			if (g_order.conv == 'o')
				length += i;
			i += cal_zero(length);
			return (i);
		}
		cal_padding(length);
		i += g_order.num_of_padding;
		if (!g_order.neg)
			put_flag(g_order.num_of_padding, ' ');
	}
	if (f)
		i += f();
	return (i);
}
