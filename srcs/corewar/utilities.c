/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:00:11 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/01 19:44:30 by qnguyen          ###   ########.fr       */
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

uint8_t	get_2bit(uint8_t byte, uint8_t position)
{
	uint8_t	bit;

	if (position == 0)
		bit = 6;
	if (position == 1)
		bit = 4;
	if (position == 2)
		bit = 2;
	return ((byte >> bit) & 0b11);
}

void	initialize(t_header_t *player)
{
	uint8_t	i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		player[i].code = NULL;
		player[i].prog_size = 0;
		player[i].id = NOT_SET;
		i++;
	}
}

void	print_arena(t_header_t *player, t_flag *flags)
{
	int			i;
	int			p_area;

	p_area = (MEM_SIZE / g_p_count);
	i = 0;
	while (i < MEM_SIZE)
	{
		if (i == p_area * 0)
			ft_printf("$g");
		else if (i == p_area * 1 )
			ft_printf("$b");
		else if (i == p_area * 2)
			ft_printf("$r");
		else if (i == p_area * 3 && g_p_count > 3)
			ft_printf("$b");
		else if (i == p_area * 0 + player[0].prog_size
			|| i == p_area * 1 + player[1].prog_size
			|| i == p_area * 2 + player[2].prog_size
			|| i == p_area * 3 + player[3].prog_size)
			ft_printf("$d");
		ft_printf("%02x ", g_arena[i++]);
		if (i % flags->byte == 0)
			ft_printf("\n");
	}
	ft_printf("\n");
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
	int	i;

	i = 0;
	// ft_printf("id: %d\n", process->process_id);
	ft_printf("prog_count: %d\n", process->prog_counter);
	ft_printf("carry: %d\n", process->carry);
	ft_printf("instruction: %d\n", process->instruction);
	ft_printf("last_live_cyc: %d\n", process->last_live_cycle);
	ft_printf("byte_next: %d\n", process->bytes_to_next_instr);
	ft_printf("wait_cycle: %d\n", process->wait_cycle);
	while (i < REG_NUMBER)
		ft_printf("%d - ", process->reg[i++]);
	ft_printf("\n\n");
}

void	print_all_process(t_process *head)
{
	while (head)
	{
		print_process(head);
		head = head->next;
	}
}
