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

char	*ft_strcat(char *dest, const char *src)
{
	int		i;
	size_t	l;

	i = 0;
	l = 0;
	while (dest[l] != '\0')
		l++;
	while (src[i] != '\0')
		dest[l++] = src[i++];
	dest[l] = '\0';
	return (dest);
}
