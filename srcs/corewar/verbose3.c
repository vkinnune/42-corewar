/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:22:36 by jrummuka          #+#    #+#             */
/*   Updated: 2022/12/05 17:47:03 by jrummuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	print_eight(t_process *process, t_game_param *game)
{
	ft_printf("Process %u hasn't lived for %u cycles (CTD %d)\n",
		process->id + 1, game->current_cycle - process->last_live_cycle,
		game->cycle_to_die);
}

void	print_sixteen(t_process *process)
{
	int	i;

	if (process->bytes_to_next > 0)
	{
		i = 0;
		ft_printf("ADV %d (0x%0.4x -> 0x%0.4x) ", process->bytes_to_next,
			process->pc, process->pc + process->bytes_to_next);
		while (i < process->bytes_to_next)
			ft_printf("%02x ", g_arena[get_position(process->pc + i++)]);
		ft_printf("\n");
	}
}
