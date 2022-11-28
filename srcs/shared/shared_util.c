/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:21:15 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/26 20:40:42 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

//get 2 hex digit from a value
uint32_t	get_2hext(uint32_t num, uint8_t position, uint8_t n)
{
	uint8_t	bit;

	bit = 8 * (n - 1 - position);
	return ((num >> bit) & 0b11111111);
}

//write n bytes of a value to a string
void	write_n_byte(t_file *file, uint32_t val, uint16_t f(uint16_t), int8_t n)
{
	uint8_t	i;

	i = 0;
	while (i < n)
	{
		if (f)
			file->idx = f(file->idx);
		file->str[file->idx++] = get_2hext(val, i++, n);
	}
}
