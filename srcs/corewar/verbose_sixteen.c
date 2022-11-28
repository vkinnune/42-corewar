/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_sixteen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:40:05 by jrummuka          #+#    #+#             */
/*   Updated: 2022/11/28 15:50:28 by jrummuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	print_sixteen(t_process *process)
{
	int	i;

	if (process->bytes_to_next > 0)
	{
		i = -1;
		ft_printf("ADV %d (0x%0.4x -> 0x%0.4x) ", process->bytes_to_next, process->pc, process->pc + process->bytes_to_next);
		while (i++ < process->bytes_to_next - 1)
		{
			if (g_arena[process->pc + i] < 16)
			{
				ft_printf("0%x ", g_arena[process->pc + i]);
			}
			else
				ft_printf("%x ", g_arena[process->pc + i]);
		}
		ft_printf("\n");
	}
}