/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:22:00 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/01 20:03:47 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	read_instruction(t_process *process)
{
	uint8_t	code;

	code = g_arena[process->prog_counter];
	// ft_printf("%02x\n", code);
	if (code >= 0x01 && code <= 0x10)
	{
		if (code != process->instruction)
		{
			process->instruction = code;
			process->wait_cycle = op_tab[code - 1].wait_cycle;
			// process->carry
			// process->bytes_to_next_instr
			// process->last_live_cycle
		}
		process->wait_cycle--; //move this to when the instruction is executed (?)
	}
	else
	{
		process->prog_counter++;
		process->wait_cycle = -1; //to make sure the next byte doesnt immediately execute
	}
}

static void	execute_le_code(t_game_param *game, t_process *process)
{
	ft_printf("Me doing %$bs now @ %$rd (ㆁᴗㆁ✿)\n", op_tab[process->instruction - 1].name, game->current_cycle);
	check_matching_arg(process);
	//func_table[process->instruction - 1](process);
}

void	processor(t_game_param *game)
{
	t_process	*current;

	current = game->head;
	while (current)
	{
		read_instruction(current);
		if (current->wait_cycle == 0)
			execute_le_code(game, current);
		current = current->next;
	}
}
