/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 21:14:57 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/03 21:36:44 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

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

static void	param_init(t_game_param *game, t_process *head)
{
	game->head = head;
	game->last_alive = -head->reg[r1];
	game->current_cycle = 1;
	game->cycle_to_die = CYCLE_TO_DIE;
	game->live_performed = 1;
	game->check_counter = 0;
}

void	check(t_game_param *game)
{
	if (game->current_cycle % game->cycle_to_die > 0)
		return ;
	kill_process(game);
	if (game->live_performed >= NBR_LIVE || game->check_counter == MAX_CHECKS)
	{
		game->cycle_to_die -= CYCLE_DELTA;
		game->check_counter = 0;
	}
	else
		game->check_counter++;
}

void	corewar(t_header_t *player, t_flag *flags)
{
	t_process		*head;
	t_game_param	game;

	arena_init(player);
	head = process_init(player);
	param_init(&game, head);
	// while (game.live_performed)//one process is living
	while (game.current_cycle < 40)
	{
		ft_printf("cycle %d: \n", game.current_cycle);
		processor(&game);
		check(&game);
		if (game.current_cycle >= flags->dump_nbr)
		{
			print_arena(player, flags);
			free_all_process(head);
			exit (0);
		} //probably will move this into a util function for a cleaner code
		game.current_cycle++;
	}
	// ft_printf("%s\n", game.last_alive);
	free_all_process(head);
}
