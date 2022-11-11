/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:22:00 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/11 19:26:13 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	read_instruction(t_process *process)
{
	uint8_t	instruction_code;

	instruction_code = g_arena[process->pc];
	if (instruction_code < 0x01 || instruction_code > 0x10)
	{
		process->pc++;
		process->wait_cycle = -1; //to make sure the next byte/cmd doesnt immediately execute
		return ;
	}
	if (process->cmd != instruction_code - 1)
	{
		process->cmd = instruction_code - 1; //-1 to match the idx on the table
		process->wait_cycle = op_tab[process->cmd].wait_cycle;
	}
	process->wait_cycle--;
}

void	update_live_player(t_game_param *game, t_process *process
					, t_arg *arg, t_header_t *player)
{
	uint16_t	i;

	i = 0;
	while (i < g_p_count)
	{
		if (arg[0].value == -player[i].id)
		{
			player->alive = 1; // reset as 0 in the next period // do we need to keep this?
			game->last_alive = player[i].id;
			if (g_flags.verbose == 1)
				ft_printf("Player %d (%s) is said to be alive\n", player->id, player->prog_name);
		}
		i++;
	}
}

static void	execute_le_code(t_game_param *game, t_process *process, t_instruct_table **instruct_table, t_header_t *player)
{
	t_arg	arg[3];

	ft_bzero((void *)arg, sizeof(arg));
	if (check_matching_arg(process, arg) != OKEI)
		return ;
	// ft_printf("\tMe do \"%s\" now (ㆁᴗㆁ✿)\n", op_tab[process->cmd].name);
	if (g_flags.verbose == 4)
		print_process(process, arg);
	instruct_table[process->cmd](process, arg, game);
	if (process->cmd == 0)
		update_live_player(game, process, arg, player);
}

void	processor(t_game_param *game, t_instruct_table **instruct_table, t_header_t *player)
{
	t_process	*process;

	process = game->head;
	while (process)
	{
		read_instruction(process);
		// if (game->current_cycle == flag->dump_nbr)
		if (process->wait_cycle == 0)
		{
			execute_le_code(game, process, instruct_table, player);
			process->pc = get_position(process->pc + process->bytes_to_next);
			// ft_printf("Me move to @%u ╰(⸝⸝⸝´꒳`⸝⸝⸝)╯ \n", process->pc);
			process->bytes_to_next = 1;
			process->cmd = -1;
		}
		process = process->next;
	}
}
