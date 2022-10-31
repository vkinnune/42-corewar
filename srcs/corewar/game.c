/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:14:42 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/31 20:29:04 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	process_kill(t_game_param *game)
{
	t_process	*prev;
	t_process	*current;

	prev = NULL;
	current = game->head;
	while (current)
	{
		if (game->cycle_to_die - current->last_live_cycle <= 0)
			delete_process(prev, current);
		current = current->next;
	}
}

void	check(t_game_param *game)
{
	process_kill(game);
	if (game->live_performed >= NBR_LIVE || game->check_counter == MAX_CHECKS)
	{
		game->cycle_to_die -= CYCLE_DELTA;
		game->check_counter = 0;
	}
	else
		game->check_counter++;
}

void	processor(t_game_param *game)
{
	t_process	*current;

	current = game->head;
	while (current)
	{
		current = current->next;
	}
}

void	vm(t_header_t *player, t_process *head)
{
	t_game_param	game;

	game.head = head;
	game.cycle = 0;
	game.cycle_to_die = CYCLE_TO_DIE;
	game.live_performed = 1;
	game.check_counter = 0;
	while (game.live_performed)//one process is living
	{
		processor(&game);
		if (game.cycle % game.cycle_to_die == 0)
			check(&game);
		game.cycle++;
	}
}