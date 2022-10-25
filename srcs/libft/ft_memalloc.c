/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 20:21:12 by qnguyen           #+#    #+#             */
/*   Updated: 2021/11/02 20:21:12 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;
	int		i;

	mem = malloc(size);
	if (mem == NULL)
		return (NULL);
	i = 0;
	while (i < (int)size)
		((char *)mem)[i++] = 0;
	return (mem);
}
