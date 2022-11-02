/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:22:00 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/02 19:24:02 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	read_instruction(t_process *process)
{
	uint8_t	code;

	code = g_arena[process->prog_counter];
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

static u_int16_t	execute_le_code(t_game_param *game, t_process *process)
{
	t_arg		*arg;
	u_int16_t	next_instruc;

	ft_printf("Me doing %$bs now @ %$rd (ㆁᴗㆁ✿)\n", op_tab[process->instruction - 1].name, game->current_cycle);
	arg = ft_memalloc(sizeof(t_arg) * 3);
	if (check_matching_arg(process, arg) == DAIJOBU)
	{
		next_instruc = assign_arg_value(arg, process);
		casting(arg);
		print_arg(process, arg);
		//func_table[process->instruction - 1](process);
	}
	free(arg);
	return (next_instruc); //make sure arena loops back
}

void	processor(t_game_param *game)
{
	t_process	*current;

	current = game->head;
	while (current)
	{
		read_instruction(current);
		// ft_printf("currently on: %s @%d\n", op_tab[current->instruction - 1].name, current->prog_counter);
		if (current->wait_cycle == 0)
		{
			current->prog_counter = execute_le_code(game, current);
			current->instruction = 0;
		}
		current = current->next;
	}
}
