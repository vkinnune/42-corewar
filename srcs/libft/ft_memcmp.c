/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:16:10 by qnguyen           #+#    #+#             */
/*   Updated: 2021/12/07 16:29:58 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((const unsigned char *)s1)[i] -
			((const unsigned char *)s2)[i] != 0)
			return (((const unsigned char *)s1)[i] -
					((const unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
