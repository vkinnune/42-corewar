/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:53:47 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/04 17:08:44 by qnguyen          ###   ########.fr       */
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

void	ld(t_process *process, t_arg *arg)
{
	//write number in argument 1 (if dir) to registry in arg2
	//or write 4bytes in argument 1 memory location (arg1 % IDX_MOD) to registry in arg2
	//if value of arg1 is 0 set carry to 1
	//if non zero set carry to 0
}

void	st(t_process *process, t_arg *arg)
{
	//write 4 bytes from reg to arg2
	//if arg2 is regisrty, you just write them to other regisrty
	//if arg2 is ind, you take currpos + arg2 % IDX_MOD, and write value to that memory address
}

void	add(t_process *process, t_arg *arg)
{
	//write 4bytes of REG in arg1 + REG in arg2 to REG in arg3
	//if value to write is 0 set carry to 1, else to 0
}

void	sub(t_process *process, t_arg *arg)
{
	//write 4bytes of REG in arg1 - REG in arg2 to REG in arg3
	//if value to write is 0 set carry to 1, else to 0
}

void	and(t_process *process, t_arg *arg)
{
	//bitwise AND
	//bitwise AND of arg1, arg2, then write result to REG in arg3
	//if arg1/2 is REG, read value from there
	//if arg1/2 is DIR, read numerical value from argument as given
	//if arg1/2 is IND, take current position + <ARGUMENT> % IDX_MOD, read 4bytes from there
}

void	or(t_process *process, t_arg *arg)
{
	//bitwise OR
	//bitwise OR of arg1, arg2, then write result to REG in arg3
	//if arg1/2 is REG, read value from there
	//if arg1/2 is DIR, read numerical value from argument as given
	//if arg1/2 is IND, take current position + <ARGUMENT> % IDX_MOD, read 4bytes from there
}

void	xor(t_process *process, t_arg *arg)
{
	//bitwise XOR
	//bitwise XOR of arg1, arg2, then write result to REG in arg3
	//if arg1/2 is REG, read value from there
	//if arg1/2 is DIR, read numerical value from argument as given
	//if arg1/2 is IND, take current position + <ARGUMENT> % IDX_MOD, read 4bytes from there
}

void	zjmp(t_process *process, t_arg *arg)
{
	//check if carry flag is 1
	//if it is the take current position + ARG1 % IDX_MOD, and update process pos to it.
}

void	ldi(t_process *process, t_arg *arg)
{

}

void	sti(t_process *process, t_arg *arg)
{

}

void	foork(t_process *process, t_arg *arg)
{

}

void	lld(t_process *process, t_arg *arg)
{

}

void	lldi(t_process *process, t_arg *arg)
{

}

void	lfork(t_process *process, t_arg *arg)
{

}

void	aff(t_process *process, t_arg *arg)
{

}
