/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:22:00 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/30 22:51:45 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

t_process	*set_processes(t_process *head, uint16_t pos, int id)
{
	t_process	*process;

	process = (t_process *)ft_memalloc(sizeof(t_process));
	check_err_malloc((void *)process);
	process->process_id = id;
	process->prog_counter = pos;
	process->next = head;
	return (process);
}

void	process_init(t_header_t *player, uint8_t p_count)
{
	uint8_t		i;
	uint16_t	p_start;
	t_process	*head;
	t_process	*new_process;

	i = 0;
	p_start = 0;
	head = NULL;
	while (i < p_count)
	{
		new_process = set_processes(head, p_start, i + 1);
		head = new_process;
		p_start += MEM_SIZE / p_count;
		i++;
	}
	print_all_process(head);
}
