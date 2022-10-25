/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 20:22:05 by qnguyen           #+#    #+#             */
/*   Updated: 2021/12/07 18:34:14 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst < src)
	{
		i = -1;
		while (++i < len)
			((char *)dst)[i] = ((const char *)src)[i];
	}
	else if (dst > src)
	{
		while ((int)--len >= 0)
			((char *)dst)[len] = ((const char *)src)[len];
	}
	return (dst);
}
