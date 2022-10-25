/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 02:18:07 by qnguyen           #+#    #+#             */
/*   Updated: 2021/12/07 18:50:46 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*temp;

	if (del == NULL || *alst == NULL)
		return ;
	while (*alst != NULL)
	{
		temp = (**alst).next;
		del((**alst).content, (**alst).content_size);
		free(*alst);
		*alst = temp;
	}
}
