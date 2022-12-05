/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:05:58 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/05 22:57:49 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	check_file_type(unsigned char *file, int16_t fd)
{
	if (get_n_byte(4, file, 0) == COREWAR_EXEC_MAGIC && fd != -1)
		return ;
	ft_out("What are you putting into me Senpai >///<");
}

void	check_file_size(uint32_t size)
{
	if (size > CHAMP_MAX_SIZE)
		ft_out("Your size is too big for me~ (⁄ ⁄>⁄ ▽ ⁄<⁄ ⁄)");
}

void	check_matching_champ_size(uint32_t byte_size, uint32_t actual)
{
	if (byte_size != actual)
		ft_out("U trying ta gaslight me with the weights, punk? (゜Д゜;)");
}

void	check_num_within_range(uint8_t num)
{
	if (num > MAX_ARGS_NUMBER || num < 1)
		ft_out("I can't handle this ammount (≧﹏≦)");
}

void	check_valid_arg(char **argv, int argc, uint8_t i)
{
	uint8_t	j;
	uint8_t	error;

	error = 0;
	j = 0;
	if (i + 1 == argc)
		error = 1;
	else
	{
		while (argv[i + 1][j])
			if (!ft_isdigit(argv[i + 1][j++]))
				error = 1;
	}
	if (error)
		ft_out("Stop teasing me B..BAKA!!! (>ε<)\"");
}
