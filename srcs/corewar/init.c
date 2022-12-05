/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:49:57 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/05 16:44:17 by jrummuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	initialize_players(t_header_t *player)
{
	uint8_t	i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		player[i].code = NULL;
		player[i].prog_size = NOT_SET;
		player[i].id = NOT_SET;
		i++;
	}
}

void	arena_init(t_header_t *player)
{
	uint8_t		i;
	uint16_t	p_start;

	ft_bzero((void *)g_arena, MEM_SIZE);
	i = 0;
	p_start = 0;
	while (i < g_p_count)
	{
		ft_memcpy(g_arena + p_start, player[i].code, player[i].prog_size);
		p_start += MEM_SIZE / g_p_count;
		i++;
	}
}

void	game_init(t_game_param *game, t_process *head)
{
	game->head = head;
	game->last_alive = -head->reg[r1];
	game->current_cycle = 1;
	game->cycle_to_die = CYCLE_TO_DIE;
	game->live_performed = 0;
	game->check_counter = 1;
}

void	flag_init(void)
{
	g_flags.dump_nbr = -1;
	g_flags.aff = NOT_SET;
	g_flags.byte = NOT_SET;
	g_flags.id = NOT_SET;
	g_flags.verbose = NOT_SET;
}
