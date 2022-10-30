/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:05:58 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/30 20:31:15 by qnguyen          ###   ########.fr       */
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

void	check_file_size(int size)
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
		ft_printf("UwU, there was problem with allocating process\n");
		// free_everything();
		exit (0);
	}
}
