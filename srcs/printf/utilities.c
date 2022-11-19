/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 11:56:51 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/19 01:58:53 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	int_converter(unsigned long long int *u, long long *n)
{
	if (n != NULL)
	{
		if (g_order.flag[0] == 0)
			*n = (int)*n;
		else if (g_order.flag[1] == 'h')
			*n = (char)*n;
		else if (g_order.flag[0] == 'h')
			*n = (short)*n;
		else if (g_order.flag[1] == 'l')
			return ;
		else if (g_order.flag[0] == 'l')
			*n = (long)*n;
		return ;
	}
	if (g_order.flag[0] == 0)
		*u = (unsigned int)*u;
	else if (g_order.flag[1] == 'h')
		*u = (unsigned char)*u;
	else if (g_order.flag[0] == 'h')
		*u = (unsigned short)*u;
	else if (g_order.flag[1] == 'l')
		return ;
	else if (g_order.flag[0] == 'l')
		*u = (unsigned long)*u;
}

void	bundling_bundler(int *length, int (*f)(void))
{
	*length += mfw(*length, f);
	if (g_order.negative_num)
	{
		g_p_str.s[g_p_str.i++] = '-';
		*length += 1;
	}
	if (g_order.conv != 's' && g_order.conv != 'c')
		*length += cal_zero(*length);
	put_flag(g_order.num_of_zeros, '0');
}

int	check_value(unsigned long long u, long long int *n)
{
	if (n != NULL && *n < 0)
	{
		g_order.pos = 0;
		g_order.space = 0;
		g_order.negative_num = 1;
		*n = -*n;
		return (*n == (long long int)-9223372036854775808u);
	}
	if (u == 0 && g_order.hash == 1 && g_order.conv != 'p')
		g_order.hash = -1;
	return (0);
}

void	check_f_value(long double *f)
{
	if (*f < 0 || 1 / *f < 0)
	{
		g_order.pos = 0;
		g_order.space = 0;
		g_order.negative_num = 1;
		*f = -*f;
	}
}

void	cpy_to_g_str(char *src, int amount)
{
	ft_memcpy(g_p_str.s + g_p_str.i, src, amount);
	g_p_str.i += amount;
}
