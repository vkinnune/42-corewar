/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 01:50:56 by qnguyen           #+#    #+#             */
/*   Updated: 2021/12/09 11:45:10 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_link;

	new_link = (t_list *)malloc(sizeof(t_list));
	if (new_link != NULL)
	{
		if (content == NULL)
		{
			(*new_link).content = NULL;
			(*new_link).content_size = 0;
		}
		else
		{
			(*new_link).content_size = content_size;
			(*new_link).content = malloc(content_size);
			if ((*new_link).content == NULL)
			{
				free(new_link);
				return (NULL);
			}
			ft_memcpy((*new_link).content, (void *)content, content_size);
		}
		(*new_link).next = NULL;
	}
	return (new_link);
}
