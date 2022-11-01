/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:14:42 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/01 16:50:09 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	check(t_game_param *game)
{
	if (game->current_cycle % game->cycle_to_die > 0) // || cycle_to_die == 0, but this never happens
		return ;
	process_kill(game);
	if (game->live_performed >= NBR_LIVE || game->check_counter == MAX_CHECKS)
	{
		game->cycle_to_die -= CYCLE_DELTA;
		game->check_counter = 0;
	}
	else
		game->check_counter++;
}

static void	param_init(t_game_param *game, t_process *head)
{
	game->head = head;
	game->last_alive = -head->reg[r1];
	game->current_cycle = 1;
	game->cycle_to_die = CYCLE_TO_DIE;
	game->live_performed = 1;
	game->check_counter = 0;
}

void	vm(t_header_t *player, t_process *head)
{
	t_game_param	game;

	param_init(&game, head);
	// while (game.live_performed)//one process is living
	while (game.current_cycle < 30)
	{
		ft_printf("cycle %d: \n", game.current_cycle);
		processor(&game);
		check(&game);
		if (game.current_cycle == g_dump_nbr)
		{
			print_arena(player);
			exit (0);
		}
		game.current_cycle++;
	}
}
