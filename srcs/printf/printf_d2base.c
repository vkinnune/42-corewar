/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_d2base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 01:18:39 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/19 01:58:56 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char	hex_digit(long long n, char x)
{
	if (n >= 0 && n < 10)
		return ('0' + n);
	if (x == 'X')
		return ('A' + n - 10);
	else
		return ('a' + n - 10);
}

void	printf_d2base(unsigned long long n, int base, char x, int i)
{
	if (n > (unsigned long long)(base - 1))
		printf_d2base(n / base, base, x, i + 1);
	g_p_str.s[g_p_str.i++] = hex_digit(n % base, x);
}
