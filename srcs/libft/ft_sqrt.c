/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 18:40:19 by okinnune          #+#    #+#             */
/*   Updated: 2022/01/12 23:11:23 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sqrt(int num)
{
	int	i;
	int	min;
	int	max;
	int	s;

	i = 1;
	s = i;
	min = i;
	max = num;
	while (s != num && max - min != 1)
	{
		if (s < num)
		{
			min = i;
			i = (i + max) / 2;
		}
		else
		{
			max = i;
			i = (i + min) / 2;
		}
		s = i * i;
	}
	return (i);
}
