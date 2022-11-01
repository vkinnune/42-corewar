/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:22:00 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/01 14:53:46 by jrummuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	delete_process(t_process *prev, t_process *delete)
{
	if (prev)
		prev->next = delete->next;
	if (delete)
		ft_memdel((void **)&delete);
}

t_process	*new_process(t_process *head, uint16_t pos, int id)
{
	t_process	*process;

	process = (t_process *)ft_memalloc(sizeof(t_process));
	check_err_malloc((void *)process);
	// process->process_id = id;
	process->prog_counter = pos;
	process->next = head;
	process->reg[r1] = -id;
	return (process);
}

t_process	*process_init(t_header_t *player)
{
	uint8_t		i;
	uint16_t	p_start;
	t_process	*head;
	t_process	*new;

	i = 0;
	p_start = 0;
	head = NULL;
	while (i < g_p_count)
	{
		new = new_process(head, p_start, player[i].id);
		head = new;
		p_start += MEM_SIZE / g_p_count;
		i++;
	}
	return (head);
}

void	process_kill(t_game_param *game)
{
	t_process	*prev;
	t_process	*process;

	prev = NULL;
	process = game->head;
	while (process)
	{
		if (game->current_cycle - process->last_live_cycle >= game->cycle_to_die)
			delete_process(prev, process);
		process = process->next;
	}
}

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
		process->wait_cycle--;
	}
	else
	{
		process->prog_counter++;
		process->wait_cycle = -1; //to make sure the next byte doesnt immediately execute
	}
}

void	execute_le_code(t_process *process)
{
	ft_printf("Me doing %$bs now (ㆁᴗㆁ✿)\n", op_tab[process->instruction - 1].name);
}

void	processor(t_game_param *game)
{
	t_process	*current;

	current = game->head;
	while (current)
	{
		read_instruction(current);
		if (current->wait_cycle == 0)
			execute_le_code(current);
		current = current->next;
	}
}
