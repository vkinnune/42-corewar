/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:00:11 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/04 20:47:44 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"
//get n byte from the arena
int	get_n_byte(uint8_t n, unsigned char *size_byte)
{
	uint8_t		i;
	uint32_t	value;

	value = 0;
	i = 0;
	while (i < n)
		value = (value * 0x100) + size_byte[i++];
	return (value);
}
//get 2 bits from a byte
uint8_t	get_2bit(uint8_t byte, uint8_t position)
{
	uint8_t	bit;

	if (position == 0)
		bit = 6;
	else if (position == 1)
		bit = 4;
	else if (position == 2)
		bit = 2;
	return ((byte >> bit) & 0b11);
}
//get 2 hex digit from a value
uint32_t	get_2hext(uint32_t num, uint8_t position)
{
	uint8_t	bit;

	if (position == 0)
		bit = 24;
	else if (position == 1)
		bit = 16;
	else if (position == 2)
		bit = 8;
	else if (position == 3)
		bit = 0;
	return ((num >> bit) & 0b11111111);
}

void	initialize_players(t_header_t *player)
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

uint16_t	get_position(uint16_t pos)
{
	return (pos % MEM_SIZE);
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
	ft_printf("id: %d\n", process->process_id);
	ft_printf("prog_count: %d\n", process->pc);
	ft_printf("carry: %d\n", process->carry);
	ft_printf("instruction: %d\n", process->cmd + 1);
	ft_printf("last_live_cyc: %d\n", process->last_live_cycle);
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

void	print_arg(t_process *process, t_arg *arg)
{
	int i = 0;

	while (i < op_tab[process->cmd].arg_amt)
	{
		ft_printf("arg %d: %u\n", i, arg[i].value);
		i++;
	}
}
