/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 20:01:21 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/05 17:48:07 by jrummuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	free_process(t_process *prev, t_process *delete)
{
	if (prev)
		prev->next = delete->next;
	if (delete)
		free(delete);
}

void	print_free_exit(t_process *head)
{
	t_process	*next;

	while (head)
	{
		next = head->next;
		free_process(0, head);
		head = next;
	}
	print_and_exit(0);
}

void	kill_process(t_game_param *game)
{
	int64_t		cycle_since_last_live;
	t_process	*prev;
	t_process	*process;
	t_process	*next;

	prev = NULL;
	process = game->head;
	while (process)
	{
		next = process->next;
		cycle_since_last_live = game->current_cycle - process->last_live_cycle;
		if (cycle_since_last_live >= game->cycle_to_die)
		{
			if (g_flags.verbose & 8)
				print_eight(process, game);
			free_process(prev, process);
			if (prev == NULL)
				game->head = next;
		}
		else
			prev = process;
		process = next;
	}
}

t_process	*new_process(t_process *head, uint16_t pos, int id)
{
	static uint64_t	process_id;
	t_process		*process;

	process = (t_process *)ft_memalloc(sizeof(t_process));
	check_err_malloc((void *)process);
	process->id = process_id++;
	process->cmd = -1;
	process->pc = pos;
	process->bytes_to_next = 1;
	process->next = head;
	process->reg[r1] = -id;
	return (process);
}

t_process	*process_init(t_header_t *player)
{
	uint8_t		i;
	uint16_t	p_start;
	t_process	*head;

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
