/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 20:01:21 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/04 15:49:24 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	free_process(t_process *prev, t_process *delete)
{
	if (prev)
		prev->next = delete->next;
	if (delete)
		ft_memdel((void **)&delete);
}

void	free_all_process(t_process *head)
{
	while (head)
	{
		free_process(0, head);
		head = head->next;
	}
}

t_process	*new_process(t_process *head, uint16_t pos, int id)
{
	static uint16_t	process_id;
	t_process		*process;

	process = (t_process *)ft_memalloc(sizeof(t_process));
	check_err_malloc((void *)process);
	process->process_id = process_id++;
	process->prog_counter = pos;
	process->bytes_to_next = 1; //move 1 up from the instruction byte
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
		head = new_process(head, p_start, player[i].id);
		p_start += MEM_SIZE / g_p_count;
		i++;
	}
	return (head);
}

void	kill_process(t_game_param *game)
{
	t_process	*prev;
	t_process	*process;

	prev = NULL;
	process = game->head;
	while (process)
	{
		if (game->current_cycle - process->last_live_cycle >= game->cycle_to_die)
			free_process(prev, process);
		process = process->next;
	}
}
