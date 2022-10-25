/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d2base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:35:47 by qnguyen           #+#    #+#             */
/*   Updated: 2022/02/11 03:16:26 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	hex_digit(long long v, char x)
{
	if (v >= 0 && v < 10)
		return ('0' + v);
	if (x == 'X')
		return ('A' + v - 10);
	else
		return ('a' + v - 10);
}

void	ft_d2base(unsigned long long n, int base, char x)
{
	if (n > (unsigned long long)(base - 1))
		ft_d2base(n / base, base, x);
	if (base < 11)
		ft_putnbr(n % base);
	else
		ft_putchar(hex_digit(n % base, x));
}

/* void	ft_hexprint(void *pointer)
{
	char		bool;
	int			dig_amnt;
	intptr_t	p;

	p = (intptr_t)pointer;
	dig_amnt = (sizeof(p) << 3) - 4;
	bool = 0;
	write(1, "0x", 2);
	while (dig_amnt >= 0)
	{
		if (!bool && hex_digit((p >> dig_amnt) & 0b1111) != '0')
			bool = 1;
		if (bool)
			ft_putchar(hex_digit((p >> dig_amnt) & 0b1111));
		dig_amnt -= 4;
	}
}

void	ft_hexprint(void *pointer)
{
	char		bool;
	int			dig_amnt;
	intptr_t	p;

	p = (intptr_t)pointer;
	dig_amnt = 15;
	bool = 0;
	write(1, "0x", 2);
	while (dig_amnt >= 0)
	{
		if (!bool && hex_digit((p / ft_pow(16, dig_amnt)) % 16) != '0')
			bool = 1;
		if (bool)
			ft_putchar(hex_digit(p / ft_pow(16, dig_amnt) % 16));
		dig_amnt--;
	}
} */
