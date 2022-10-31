/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:22:00 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/31 17:46:00 by jrummuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void		delete_process(t_process *prev, t_process *delete)
{
	prev->next = delete->next;
	ft_memdel((void **)&delete);
}

t_process	*new_process(t_process *head, uint16_t pos, int id)
{
	t_process	*process;
	uint8_t		i;

	process = (t_process *)ft_memalloc(sizeof(t_process));
	check_err_malloc((void *)process);
	process->process_id = id;
	process->prog_counter = pos;
	process->next = head;
	i = 0;
	while (i < REG_NUMBER)
		process->reg[i++] = 0;
	return (process);
}

void	process_init(t_header_t *player)
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
	print_all_process(head);
}
