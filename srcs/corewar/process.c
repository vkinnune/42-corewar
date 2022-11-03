/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:22:00 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/03 21:34:32 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	read_instruction(t_process *process)
{
	uint8_t	code;

	code = g_arena[process->prog_counter];
	// ft_printf("instruc: %s\n", op_tab[code - 1].name);
	if (code < 0x01 || code > 0x10)
	{
		process->prog_counter++;
		process->wait_cycle = -1; //to make sure the next byte doesnt immediately execute
		return ;
	}
	if (code != process->instruction)
	{
		process->instruction = code;
		process->wait_cycle = op_tab[code - 1].wait_cycle;
	}
	process->wait_cycle--;
}

static u_int16_t	execute_le_code(t_game_param *game, t_process *process)
{
	t_arg		arg[3];
	u_int16_t	next_instruc;

	ft_bzero((void *)arg, sizeof(arg));
	ft_printf("%d doing %$bs now @ %$rd (ㆁᴗㆁ✿)\n", process->process_id, op_tab[process->instruction - 1].name, game->current_cycle);
	if (check_matching_arg(process, arg) == OKEI)
	{
		next_instruc = assign_arg_value(arg, process);
		// print_arg(process, arg);
		// func_table[process->instruction - 1](process);
		// live() process->last_live_cycle
		// process->carry
	}
	return (next_instruc);
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
			current->prog_counter = (current->prog_counter + execute_le_code(game, current)) % MEM_SIZE;
			current->instruction = 0;
		}
		current = current->next;
	}
}
