/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:00:11 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/26 20:39:59 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

//get n byte from the arena
int	get_n_byte(uint8_t n, unsigned char *data, uint32_t idx)
{
	uint8_t		i;
	uint32_t	value;

	value = 0;
	i = 0;
	if (data)
	{
		while (i < n)
			value = (value * 0x100) + data[idx + i++];
	}
	else
		while (i < n)
			value = (value * 0x100) + g_arena[get_position(idx + i++)];
	return (value);
}

//get 2 bits from a byte
uint8_t	get_2bit(uint8_t byte, uint8_t position)
{
	uint8_t	bit;

	bit = 2 * (3 - position);
	return ((byte >> bit) & 0b11);
}
