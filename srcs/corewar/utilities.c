/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:00:11 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/05 23:04:03 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

//get n byte from the arena
int32_t	get_n_byte(uint8_t n, unsigned char *data, uint32_t idx)
{
	uint8_t		i;
	int32_t		value;

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

uint16_t	get_position(uint16_t pos)
{
	if (pos < 4096)
		return (pos);
	return (pos % MEM_SIZE);
}

void	get_arg_without_arg_byte(t_process *process, t_arg *arg)
{
	uint8_t		dir_size;

	dir_size = DIR_SIZE;
	if (g_op_tab[process->cmd].dir_size)
		dir_size = 2;
	arg->value = get_n_byte(dir_size, 0, process->pc + 1);
}
