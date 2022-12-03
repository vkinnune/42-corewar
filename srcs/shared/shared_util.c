/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:21:15 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/03 18:30:35 by qnguyen          ###   ########.fr       */
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

//write n bytes of a value to a memory location
//pass 0 for f() in asm
//pass get_position for f() in corewar to loop within the arena
void	write_n_byte(t_file *file, uint32_t val
		, uint16_t get_pos(uint16_t), int8_t n)
{
	uint8_t	i;

	i = 0;
	while (i < n)
	{
		if (get_pos)
			file->idx = get_pos(file->idx);
		file->str[file->idx++] = get_2hext(val, i++, n);
	}
}

//as it says
void	print_and_exit(int err_no)
{
	write(1, g_p_str.s, g_p_str.i);
	exit(err_no);
}

//exit when malloc fails
void	check_err_malloc(void *ptr)
{
	if (!ptr)
	{
		ft_printf("You already had my everything Senpai UwU \n");
		print_and_exit (0);
	}
}
