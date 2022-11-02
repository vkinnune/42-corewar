/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:05:58 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/02 18:39:05 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	check_file_type(unsigned char *file)
{
	if (get_n_byte(4, file) == COREWAR_EXEC_MAGIC)
		return ;
	ft_printf("What are you putting into me Senpai >///<\n");
	exit (0);
}

void	check_file_size(uint32_t size)
{
	if (size > CHAMP_MAX_SIZE)
	{
		ft_printf("Your size is too big for me~ (⁄ ⁄>⁄ ▽ ⁄<⁄ ⁄)\n");
		exit(0);
	}
}

void	check_err_malloc(void *ptr)
{
	if (!ptr)
	{
		ft_printf("You already had my everything Senpai UwU \n");
		// free_everything();
		exit (0);
	}
}

void	check_num_within_range(uint8_t num)
{
	if (num > MAX_ARGS_NUMBER || num < 1)
	{
		ft_printf("I can't handle this ammount (≧﹏≦)\n");
		exit(0);
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
		exit(0);
	}
}

void	check_existing_id(int8_t id)
{
	if (id != NOT_SET)
	{
		ft_printf("Pwayers can has no same id (っ´ω｀c)\n");
		exit(0);
	}
}

void	check_missing_id(int8_t id)
{
	if (id == NOT_SET)
	{
		ft_printf("There's empty space in my heart Senpai (⁄ ⁄•⁄ω⁄•⁄ ⁄)\n");
		exit(0);
	}
}

void	print_man_page(void)
{
	ft_printf("man page goes here\n");
	exit(0);
}
