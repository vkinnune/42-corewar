/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:05:58 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/31 10:51:08 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	check_file_type(unsigned char *file)
{
	if (get_4byte(file) == COREWAR_EXEC_MAGIC)
		return ;
	ft_printf("What are you putting into me senpai >///<\n");
	exit (0);
}

void	check_file_size(uint32_t size)
{
	if (size > CHAMP_MAX_SIZE)
	{
		ft_printf("Your size is too big for me~ (≥.≤)\n");
		exit(0);
	}
}

void	check_err_malloc(void *ptr)
{
	if (!ptr)
	{
		ft_printf("UwU there was some pwobwem with allocating memowy\n");
		// free_everything();
		exit (0);
	}
}

void	check_num_within_range(uint8_t num)
{
	if (num > MAX_ARGS_NUMBER || num < 1)
	{
		ft_printf("I can't handle this much (°Д°*)\n");
		exit(0);
	}
}

uint32_t	check_valid_arg(unsigned char *arg)
{
	uint8_t	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			ft_printf("Nyaaa!! (>ε<)\" stop teasing me Senpai!!!~\n");
			exit(0);
		}
		i++;
	}
	return (ft_atoi(arg));
}

void	print_man_page(void)
{
	ft_printf("man page goes here\n");
	exit(0);
}
