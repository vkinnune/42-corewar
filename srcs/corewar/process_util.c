/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 20:01:21 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/02 00:24:02 by qnguyen          ###   ########.fr       */
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

void	free_and_exit(t_process *head)
{
	t_process	*next;

	while (head)
	{
		next = head->next;
		free_process(0, head);
		head = next;
	}
	exit(0);
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
				ft_printf("Process %u hasn't lived for %u cycles (CTD %d)\n", process->id + 1, game->current_cycle - process->last_live_cycle, game->cycle_to_die);
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

void	get_arg_without_arg_byte(t_process *process, t_arg *arg)
{
	uint8_t		dir_size;

	dir_size = DIR_SIZE;
	if (op_tab[process->cmd].dir_size)
		dir_size = 2;
	arg->value = get_n_byte(dir_size, 0, process->pc + 1);
}
