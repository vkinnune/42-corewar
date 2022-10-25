/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_udiglen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 03:41:46 by qnguyen           #+#    #+#             */
/*   Updated: 2022/02/11 03:41:57 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_udiglen(unsigned long long n, int base)
{
	int	i;

	i = 1;
	while (n / base > 0)
	{
		n = n / base;
		i++;
	}
	return (i);
}
