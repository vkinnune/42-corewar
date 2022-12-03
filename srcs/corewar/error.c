/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:05:58 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/03 18:30:15 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	check_file_type(unsigned char *file, int16_t fd)
{
	if (get_n_byte(4, file, 0) == COREWAR_EXEC_MAGIC && fd != -1)
		return ;
	ft_printf("What are you putting into me Senpai >///<\n");
	print_and_exit(0);
}

void	check_file_size(uint32_t size)
{
	if (size > CHAMP_MAX_SIZE)
	{
		ft_printf("Your size is too big for me~ (⁄ ⁄>⁄ ▽ ⁄<⁄ ⁄)\n");
		print_and_exit(0);
	}
}

void	check_matching_champ_size(uint32_t byte_size, uint32_t actual)
{
	if (byte_size != actual)
	{
		ft_printf("U trying ta gaslight me with the weights, punk? (゜Д゜;)\n");
		print_and_exit(0);
	}
}

void	check_num_within_range(uint8_t num)
{
	if (num > MAX_ARGS_NUMBER || num < 1)
	{
		ft_printf("I can't handle this ammount (≧﹏≦)\n");
		print_and_exit(0);
	}
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
	{
		ft_printf("Stop teasing me B..BAKA!!! (>ε<)\"\n");
		print_and_exit(0);
	}
}

void	check_existing_id(int8_t id)
{
	ft_printf("%d\n", id);
	if (id != NOT_SET)
	{
		ft_printf("Pwayers can has no same id (っ´ω｀c)\n");
		print_and_exit(0);
	}
}

void	check_missing_id(int8_t id)
{
	if (id == NOT_SET)
	{
		ft_printf("There's empty space in my heart Senpai (⁄ ⁄•⁄ω⁄•⁄ ⁄)\n");
		print_and_exit(0);
	}
}
