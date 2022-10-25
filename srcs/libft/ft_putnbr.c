/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 05:48:03 by qnguyen           #+#    #+#             */
/*   Updated: 2022/03/14 17:24:01 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(long long n)
{
	unsigned long long	u;

	if (n < 0)
	{
		write(1, "-", 1);
		n++;
		u = (unsigned long long)-n + 1;
	}
	else
		u = (unsigned long long)n;
	if (u > 9)
		ft_putnbr(u / 10);
	ft_putchar(u % 10 + '0');
}

/* void	ft_putnbr(long long n)
{
	int	i;
	int	i2;

	i = ft_diglen(n);
	i2 = i;
	if (n < 0)
	{
		write(1, "-", 1);
		i2++;
	}
	while (i-- > 0)
		ft_putchar((n / ft_pow(10, i) % 10) * (-(n < 0) | 0x1) + '0');
}
 */