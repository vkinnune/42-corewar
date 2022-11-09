/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 21:14:57 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/09 18:22:12 by qnguyen          ###   ########.fr       */
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
	// ft_printf("\tc2d: %d --- res: %d\n",game->cycle_to_die, game->current_cycle % game->cycle_to_die );
	if (game->current_cycle % game->cycle_to_die > 0 && game->cycle_to_die > 0)
		return ;
	ft_printf("\tc2d: %d --- res: %d\n",game->cycle_to_die, game->current_cycle % game->cycle_to_die );
	if (game->current_cycle >= 57900)
		sleep(2);
	kill_process(game);
	if (game->live_performed >= NBR_LIVE || game->check_counter == MAX_CHECKS)
	{
		game->cycle_to_die -= CYCLE_DELTA;
		ft_printf("\treduce in cycle %u%\n", game->current_cycle);
		ft_printf("\tcycle to die is now %u%\n", game->cycle_to_die);
		sleep(2);
		// if (game->cycle_to_die < 50)
			// sleep(1);
		game->check_counter = 0;
	}
	else
		game->check_counter++;
	game->live_performed = 0;
}

void	corewar(t_header_t *player, t_flag *flags)
{
	t_process			*head;
	t_game_param		game;
	t_instruct_table	*instruct_table[16];

	arena_init(player);
	head = process_init(player);
	param_init(&game, head);
	instr_table_init(instruct_table);
	while (game.head)//one process is living
	{
		if (game.current_cycle >= 57900)
			ft_printf("\ncycle %$ru: \n", game.current_cycle);
		processor(&game, instruct_table, player);
		check(&game);
		if (game.current_cycle >= flags->dump_nbr)
		{
			print_arena(player, flags);
			free_all_process(head);
			exit (0);
		} //probably will move this into a util function for a cleaner code
		game.current_cycle++;
	}
	ft_printf("#%d won\n", game.last_alive);
	// free_all_process(head);
}
