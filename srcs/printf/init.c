/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 00:09:24 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/19 02:37:38 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	initialize_order(int fd)
{
	g_order.space = 0;
	g_order.pos = 0;
	g_order.hash = 0;
	g_order.zero = 0;
	g_order.neg = 0;
	g_order.mfw = 0;
	g_order.prec = 0;
	g_order.flag[0] = 0;
	g_order.flag[1] = 0;
	g_order.conv = 0;
	g_order.base = 10;
	g_order.num_of_padding = 0;
	g_order.num_of_zeros = 0;
	g_order.negative_num = 0;
	g_order.func_idx = -1;
	g_order.color = 0;
	g_order.fd = fd;
}

void	printf_init(int *fd, int *char_count)
{
	*fd = 1;
	ft_strcpy(g_printf_default_color, "\x1b[0m");
	*char_count = 0;
	g_p_str.i = 0;
	ft_bzero(g_p_str.s, STRING_SIZE);
}
