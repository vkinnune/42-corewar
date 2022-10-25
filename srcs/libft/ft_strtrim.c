/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:04:09 by qnguyen           #+#    #+#             */
/*   Updated: 2021/12/02 17:58:10 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(s) - 1;
	while (ft_isspace(s[i]) == 1)
		i++;
	while (ft_isspace(s[j]) == 1)
		j--;
	if (i > j)
		return (ft_strdup(""));
	return (ft_strsub(s, i, (j - i + 1)));
}
