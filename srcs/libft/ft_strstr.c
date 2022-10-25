/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 21:53:11 by qnguyen           #+#    #+#             */
/*   Updated: 2021/10/31 21:53:11 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	while (str[i] != '\0')
	{
		while (str[i + i2] == to_find[i2] && to_find[i2] != '\0')
			i2++;
		if (to_find[i2] == '\0')
			return ((char *)&str[i]);
		else
			i2 = 0;
		i++;
	}
	if (to_find[i2] == '\0')
		return ((char *)&str[i]);
	return (NULL);
}
