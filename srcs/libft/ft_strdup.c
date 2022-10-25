/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:49:29 by qnguyen           #+#    #+#             */
/*   Updated: 2021/12/07 16:34:13 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*buf;
	size_t	i;

	buf = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (buf == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		buf[i] = src[i];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}
