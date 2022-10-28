/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:05:58 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/28 13:13:39 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int	check_file_type(unsigned char *file)
{
	if (get_4byte(file) == COREWAR_EXEC_MAGIC)
		return (4);
	ft_printf("What are you putting into me senpai >///<\n");
	//free_everything();
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
