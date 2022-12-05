/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:44:27 by vkinnune          #+#    #+#             */
/*   Updated: 2022/12/05 22:42:39 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_out(char *reason)
{
	while (*reason)
	{
		write(2, reason, 1);
		reason++;
	}
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
	return (EXIT_FAILURE);
}
