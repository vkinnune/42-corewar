/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 21:14:57 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/11 19:43:28 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	instr_table_init(t_instruct_table **instruct_table)
{
	instruct_table[0] = live;
	instruct_table[1] = ld;
	instruct_table[2] = st;
	instruct_table[3] = add;
	instruct_table[4] = sub;
	instruct_table[5] = and;
	instruct_table[6] = or;
	instruct_table[7] = xor;
	instruct_table[8] = zjmp;
	instruct_table[9] = ldi;
	instruct_table[10] = sti;
	instruct_table[11] = foork;
	instruct_table[12] = lld;
	instruct_table[13] = lldi;
	instruct_table[14] = lfork;
	instruct_table[15] = aff;
}

void	check(t_game_param *game)
{
	static int	cycle_count;

	if (cycle_count++ < game->cycle_to_die - 1)
		return ;
	kill_process(game);
	if (game->live_performed >= NBR_LIVE || game->check_counter == MAX_CHECKS)
	{
		game->cycle_to_die -= CYCLE_DELTA;
		game->check_counter = 0;
		if (g_flags.verbose == 2)
			ft_printf("Cycle to die is now %d\n", game->cycle_to_die);
	}
	game->check_counter++;
	game->live_performed = 0;
	cycle_count = 0;
}

void	corewar(t_header_t *player)
{
	t_process			*head;
	t_game_param		game;
	t_instruct_table	*instruct_table[16];

	arena_init(player);
	head = process_init(player);
	game_init(&game, head);
	instr_table_init(instruct_table);
	while (game.head)
	{
		if (g_flags.verbose == 2)
			ft_printf("It is now cycle %u\n", game.current_cycle);
		processor(&game, instruct_table, player);
		check(&game);
		if (game.current_cycle >= g_flags.dump_nbr)
		{
			print_arena(player);
			// ft_printf("cycle to die %u\n", game.cycle_to_die);
			// ft_printf("check counter: %d\n", game.check_counter);
			// ft_printf("live during period: %d\n", game.live_performed);
			free_all_process(game.head);
			exit (0);
		}
		game.current_cycle++;
	}
	// ft_printf("Contestant %d, \"%s\", has won !\n", game.last_alive, player[game.last_alive - 1].prog_name);
	// ft_printf("@%d\n", game.current_cycle - 1);
	free_all_process(game.head);
}
