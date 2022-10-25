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

void	*ft_calloc(size_t count, size_t size)
{
	void		*mem;
	size_t		i;

	if (count <= 0 || size <= 0)
		return (NULL);
	mem = malloc(count * size);
	if (mem == NULL)
		return (NULL);
	i = 0;
	while (i < size)
		((char *)mem)[i++] = 0;
	return (mem);
}
