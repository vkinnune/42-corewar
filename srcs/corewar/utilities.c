/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:00:11 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/30 22:44:18 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int	get_4byte(unsigned char *size_byte)
{
	uint8_t		i;
	uint32_t	value;

	value = 0;
	i = 0;
	while (i < 4)
		value = (value * 0x100) + size_byte[i++];
	return (value);
}

void	initialize(t_header_t *player)
{
	uint8_t	i;

	i = 0;
	while (i < 4)
	{
		player[i].code = NULL;
		player[i].prog_size = 0;
		i++;
	}
}

//test functions

void	print_mem(int size, unsigned char *mem)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_printf("%02x ", mem[i++]);
		if (i % 64 == 0)
			ft_printf("\n");
	}
	ft_printf("\n");
}

void	print_process(t_process *process)
{
	ft_printf("id: %d\n", process->process_id);
	ft_printf("prog_count: %d\n", process->prog_counter);
	ft_printf("carry: %d\n", process->carry);
	ft_printf("instruction: %d\n", process->instruction);
	ft_printf("last_live_cyc: %d\n", process->last_live_cycle);
	ft_printf("byte_next: %d\n", process->bytes_to_next_instr);
	ft_printf("wait_cycle: %d\n", process->wait_cycle);
	int i = 0;
	while (i < REG_NUMBER)
		ft_printf("%d - ", process->reg[i++]);
	ft_printf("\n\n");
}

void	print_all_process(t_process *head)
{
	while(head)
	{
		print_process(head);
		head = head->next;
	}
}
