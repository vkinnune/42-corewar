/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:53:47 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/04 20:40:11 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	live(t_process *process, t_arg *arg, t_header_t *player)
{
	//update process->last_live_cycle
	int	i = 0;
	while (i  < g_p_count)
	{
		if (arg[0].value == -player[i].id)
		{
			//player[i] == alive();
			//game->last_alive == player[i];
		}
	}
	//
}

void	ld(t_process *process, t_arg *arg, t_header_t *player)
{
	//write number in argument 1 (if dir) to registry in arg2
	//or write 4bytes in argument 1 memory location (arg1 % IDX_MOD) to registry in arg2
	//if value of arg1 is 0 set carry to 1
	//if non zero set carry to 0
	uint32_t	value;

	value = get_arg_value(process, &arg[0]);
	if (arg[0].type == IND_CODE)
		value = get_n_byte(4, &g_arena[value]);
	process->reg[arg[1].value] = value;
	process->carry = (process->reg[arg[1].value] == 0);
}

void	st(t_process *process, t_arg *arg, t_header_t *player)
{
	//write 4 bytes from reg to arg2
	//if arg2 is regisrty, you just write them to other regisrty
	//if arg2 is ind, you take currpos + arg2 % IDX_MOD, and write value to that memory address
	uint32_t	value;

	value = get_arg_value(process, &arg[0]);
	if (arg[1].type == IND_CODE)
		write_4byte(process, value, get_arg_value(process, &arg[1]));
	else
		g_arena[arg[1].value] = value;
}

void	add(t_process *process, t_arg *arg, t_header_t *player)
{
	//write 4bytes of REG in arg1 + REG in arg2 to REG in arg3
	//if value to write is 0 set carry to 1, else to 0
}

void	sub(t_process *process, t_arg *arg, t_header_t *player)
{
	//write 4bytes of REG in arg1 - REG in arg2 to REG in arg3
	//if value to write is 0 set carry to 1, else to 0
}

void	and(t_process *process, t_arg *arg, t_header_t *player)
{
	//bitwise AND
	//bitwise AND of arg1, arg2, then write result to REG in arg3
	//if arg1/2 is REG, read value from there
	//if arg1/2 is DIR, read numerical value from argument as given
	//if arg1/2 is IND, take current position + <ARGUMENT> % IDX_MOD, read 4bytes from there
}

void	or(t_process *process, t_arg *arg, t_header_t *player)
{
	//bitwise OR
	//bitwise OR of arg1, arg2, then write result to REG in arg3
	//if arg1/2 is REG, read value from there
	//if arg1/2 is DIR, read numerical value from argument as given
	//if arg1/2 is IND, take current position + <ARGUMENT> % IDX_MOD, read 4bytes from there
}

void	xor(t_process *process, t_arg *arg, t_header_t *player)
{
	//bitwise XOR
	//bitwise XOR of arg1, arg2, then write result to REG in arg3
	//if arg1/2 is REG, read value from there
	//if arg1/2 is DIR, read numerical value from argument as given
	//if arg1/2 is IND, take current position + <ARGUMENT> % IDX_MOD, read 4bytes from there
}

void	zjmp(t_process *process, t_arg *arg, t_header_t *player)
{
	//check if carry flag is 1
	//if it is the take current position + ARG1 % IDX_MOD, and update process pos to it.
}

void	ldi(t_process *process, t_arg *arg, t_header_t *player)
{
	uint16_t	position;

	position = process->pc + (get_arg_value(process, &arg[0]) + get_arg_value(process, &arg[1])) % IDX_MOD;
	process->reg[arg[2].value] = get_n_byte(4, &g_arena[position]);
	// ft_printf("pos: %u\n", position);
	// ft_printf("reg value: %u\n", process->reg[arg[2].value]);
}

void	sti(t_process *process, t_arg *arg, t_header_t *player)
{
	uint16_t	position;

	position = process->pc + (get_arg_value(process, &arg[1]) + get_arg_value(process, &arg[2])) % IDX_MOD;
	write_4byte(process, get_arg_value(process, &arg[0]), position);
}

void	foork(t_process *process, t_arg *arg, t_header_t *player)
{

}

void	lld(t_process *process, t_arg *arg, t_header_t *player)
{

}

void	lldi(t_process *process, t_arg *arg, t_header_t *player)
{

}

void	lfork(t_process *process, t_arg *arg, t_header_t *player)
{

}

void	aff(t_process *process, t_arg *arg, t_header_t *player)
{

}
