/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:22:00 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/04 17:58:30 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	read_instruction(t_process *process)
{
	uint8_t	instruction_code;

	instruction_code = g_arena[process->prog_counter];
	// ft_printf("instruc: %s\n", op_tab[instruction_code - 1].name);
	if (instruction_code < 0x01 || instruction_code > 0x10)
	{
		process->prog_counter++;
		process->wait_cycle = -1; //to make sure the next byte doesnt immediately execute
		return ;
	}
	if (process->cmd != instruction_code - 1)
	{
		process->cmd = instruction_code - 1;
		process->wait_cycle = op_tab[process->cmd].wait_cycle;
	}
	process->wait_cycle--;
}

static void	execute_le_code(t_game_param *game, t_process *process)
{
	t_arg		arg[3];

	ft_bzero((void *)arg, sizeof(arg));
	ft_printf("%d is on %$gs @%$bu:\n", process->process_id, op_tab[process->cmd].name, process->prog_counter);
	if (check_matching_arg(process, arg) != OKEI)
		return ;
	ft_printf("\tMe do %$gs now (ㆁᴗㆁ✿)\n", op_tab[process->cmd].name, game->current_cycle);
	casting(process, arg);
	// print_arg(process, arg);
	// func_table[process->cmd](process);
	// process->carry
}

void	processor(t_game_param *game)
{
	t_process	*process;

	process = game->head;
	while (process)
	{
		read_instruction(process);
		if (process->wait_cycle == 0)
		{
			execute_le_code(game, process);
			process->prog_counter += process->bytes_to_next;
			process->prog_counter = get_position(process->prog_counter);
			ft_printf("Me move to @%$bu ╰(⸝⸝⸝´꒳`⸝⸝⸝)╯ \n", process->prog_counter);
			process->bytes_to_next = 1;
			process->cmd = 0;
		}
		process = process->next;
	}
}
