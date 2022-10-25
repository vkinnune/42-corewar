/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linkdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 06:22:30 by qnguyen           #+#    #+#             */
/*   Updated: 2021/12/12 04:52:04 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_linkdel(void *content, size_t content_size)
{
	ft_memset(content, '\0', content_size);
	free(content);
	content = NULL;
}
