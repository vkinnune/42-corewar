/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:00:11 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/11 19:38:35 by qnguyen          ###   ########.fr       */
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

static void	colored_arena(t_header_t *player, int i, int p_area)
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
}

void	print_arena(t_header_t *player)
{
	int			i;
	int			p_area;

	p_area = (MEM_SIZE / g_p_count);
	i = 0;
	while (i < MEM_SIZE)
	{
		// colored_arena(player, i, p_area);
		if (i % g_flags.byte == 0)
		{
			if (i != 0)
				ft_printf("\n%#06x : ", i);
			else
				ft_printf("0x0000 : "); // quick fix until i fix my printf
		}
		ft_printf("%02x ", g_arena[i++]);
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

void	print_process(t_process *process, t_arg *arg)
{
	int	i;

	i = 0;
	ft_printf("P    %d | ", process->id + 1);
	ft_printf("%s ", op_tab[process->cmd].name);
	print_arg(process, arg);
	ft_printf("\n");
	// ft_printf("\tprog_count: %d\n", process->pc);
}

void	print_arg(t_process *process, t_arg *arg)
{
	int i = 0;

	while (i < op_tab[process->cmd].arg_amt)
	{
		ft_printf("%u ", arg[i].value);
		i++;
	}
}
