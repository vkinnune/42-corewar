/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 00:34:15 by qnguyen           #+#    #+#             */
/*   Updated: 2021/10/30 00:34:15 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	int		i;
	int		l_d;

	l_d = ft_strlen(dest);
	if ((int)size <= l_d)
		return (ft_strlen(src) + (int) size);
	i = -1;
	while (++i < (int)size - l_d - 1 && src[i] != '\0')
		dest[l_d + i] = src[i];
	if (src[i] == '\0')
		dest[l_d + i] = '\0';
	else
		dest[size - 1] = '\0';
	return (ft_strlen(src) + l_d);
}
