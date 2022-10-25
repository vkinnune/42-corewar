/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 02:27:06 by qnguyen           #+#    #+#             */
/*   Updated: 2021/12/10 16:42:49 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*map;
	t_list	*temp;

	if (f == NULL || lst == NULL)
		return (NULL);
	map = f(lst);
	if (map == NULL)
		return (NULL);
	temp = map;
	lst = (*lst).next;
	while (lst != NULL)
	{
		(*temp).next = f(lst);
		if ((*temp).next == NULL)
		{
			ft_lstdel(&map, ft_linkdel);
			return (NULL);
		}
		temp = (*temp).next;
		lst = (*lst).next;
	}
	(*temp).next = NULL;
	return (map);
}
