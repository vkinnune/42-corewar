/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 07:40:07 by qnguyen           #+#    #+#             */
/*   Updated: 2022/03/27 01:50:20 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(long long n, int fd)
{
	unsigned long long	u;

	if (n < 0)
	{
		write(fd, "-", 1);
		n++;
		u = (unsigned long long)-n + 1;
	}
	else
		u = (unsigned long long)n;
	if (u > 9)
		ft_putnbr_fd(u / 10, fd);
	ft_putchar_fd(u % 10 + '0', fd);
}
