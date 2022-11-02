/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:53:47 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/02 15:13:33 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	sti(t_process *process)
{
	uint8_t	arg[3];

	if (check_matching_arg(process, arg) != DAIJOBU)
	{
		ft_printf("$rdame dayo$d\n");
		process->prog_counter++;
		return;
	}
	ft_printf("$gdaijobu da$d\n");

}
