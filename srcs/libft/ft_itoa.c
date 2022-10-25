/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 05:48:16 by qnguyen           #+#    #+#             */
/*   Updated: 2022/04/23 11:06:57 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(long long n)
{
	char	*s;
	int		c;

	c = ft_diglen(n);
	s = (char *)malloc(sizeof(char) * (c + 1));
	if (n < -9223372036854775807)
		return (ft_strcpy(s, "-9223372036854775808"));
	if (s == NULL)
		return (NULL);
	if (n < 0)
	{
		s[0] = '-';
		n = -n;
	}
	s[c--] = '\0';
	while (n / 10 > 0)
	{
		s[c--] = (n % 10) + '0';
		n = n / 10;
	}
	s[c] = n + '0';
	return (s);
}
