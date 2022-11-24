/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 21:14:57 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/18 22:28:53 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	set_instr_table(t_table *tab)
{
	tab->instruct_table[0] = live;
	tab->instruct_table[1] = l_ld;
	tab->instruct_table[2] = st;
	tab->instruct_table[3] = add_sub;
	tab->instruct_table[4] = add_sub;
	tab->instruct_table[5] = and_or_xor;
	tab->instruct_table[6] = and_or_xor;
	tab->instruct_table[7] = and_or_xor;
	tab->instruct_table[8] = zjmp;
	tab->instruct_table[9] = ldi;
	tab->instruct_table[10] = sti;
	tab->instruct_table[11] = l_foork;
	tab->instruct_table[12] = l_ld;
	tab->instruct_table[13] = lldi;
	tab->instruct_table[14] = l_foork;
	tab->instruct_table[15] = aff;
}

static void	set_verb_table(t_table *tab)
{
	tab->verbose_table[0] = verbose_live;
	tab->verbose_table[1] = verbose_l_ld;
	tab->verbose_table[2] = verbose_st;
	tab->verbose_table[3] = verbose_add_sub;
	tab->verbose_table[4] = verbose_add_sub;
	tab->verbose_table[5] = verbose_and_or_xor;
	tab->verbose_table[6] = verbose_and_or_xor;
	tab->verbose_table[7] = verbose_and_or_xor;
	tab->verbose_table[8] = verbose_zjmp;
	tab->verbose_table[9] = verbose_l_ldi;
	tab->verbose_table[10] = verbose_sti;
	tab->verbose_table[11] = verbose_l_foork;
	tab->verbose_table[12] = verbose_l_ld;
	tab->verbose_table[13] = verbose_l_ldi;
	tab->verbose_table[14] = verbose_l_foork;
	tab->verbose_table[15] = 0;
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
		if (g_flags.verbose & 2)
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
	t_table				tab;

	arena_init(player);
	head = process_init(player);
	game_init(&game, head);
	set_instr_table(&tab);
	set_verb_table(&tab);
	while (game.head)
	{
		if (g_flags.verbose & 2)
			ft_printf("It is now cycle %u\n", game.current_cycle);
		processor(&game, &tab, player);
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
	ft_printf("Contestant %d, \"%s\", has won !\n", game.last_alive, player[game.last_alive - 1].prog_name);
	// ft_printf("@%d\n", game.current_cycle - 1);
	free_all_process(game.head);
}
