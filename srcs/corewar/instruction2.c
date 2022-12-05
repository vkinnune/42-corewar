/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:19:10 by jrummuka          #+#    #+#             */
/*   Updated: 2022/12/05 17:52:06 by jrummuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	and_or_xor(t_process *process, t_arg *arg, t_game_param *game)
{
	uint8_t	i;

	i = 0;
	while (i < 2)
	{
		arg[i].value = get_arg_value(process, &arg[i]);
		if (arg[i].type == IND_CODE)
			arg[i].value = get_n_byte(4, 0, arg[i].value);
		i++;
	}
	if (process->cmd == 5)
		process->reg[arg[2].value] = arg[0].value & arg[1].value;
	else if (process->cmd == 6)
		process->reg[arg[2].value] = arg[0].value | arg[1].value;
	else
		process->reg[arg[2].value] = arg[0].value ^ arg[1].value;
	process->carry = (process->reg[arg[2].value] == 0);
	(void)game;
}

void	zjmp(t_process *process, t_arg *arg, t_game_param *game)
{
	int32_t	position;

	position = process->pc + ((int16_t)arg[0].value % IDX_MOD);
	position = get_position(position);
	process->bytes_to_next += 2;
	if (process->carry == 1)
	{
		process->bytes_to_next = 0;
		process->pc = position;
	}
	(void)game;
}

void	ldi(t_process *process, t_arg *arg, t_game_param *game)
{
	int32_t	position;

	arg[0].value = get_arg_value(process, &arg[0]);
	if (arg[0].type == IND_CODE)
	{
		arg[0].value = get_position(arg[0].value);
		arg[0].value = get_n_byte(4, 0, arg[0].value);
	}
	arg[1].value = get_arg_value(process, &arg[1]);
	position = (arg[0].value + arg[1].value) % IDX_MOD;
	position = get_position(process->pc + position);
	process->reg[arg[2].value] = get_n_byte(4, 0, position);
	(void)game;
}

void	lldi(t_process *process, t_arg *arg, t_game_param *game)
{
	int32_t	position;

	if (arg[0].type == IND_CODE)
	{
		arg[0].value = process->pc + (int16_t)(arg[0].value);
		arg[0].value = get_position(arg[0].value);
		arg[0].value = get_n_byte(4, 0, arg[0].value);
	}
	else
		arg[0].value = get_arg_value(process, &arg[0]);
	arg[1].value = get_arg_value(process, &arg[1]);
	position = arg[0].value + arg[1].value;
	position = get_position(process->pc + position);
	process->reg[arg[2].value] = get_n_byte(4, 0, position);
	process->carry = (process->reg[arg[2].value] == 0);
	(void)game;
}

void	sti(t_process *process, t_arg *arg, t_game_param *game)
{
	int32_t	position;
	t_file	arena;

	arg[1].value = get_arg_value(process, &arg[1]);
	if (arg[1].type == IND_CODE)
	{
		arg[1].value = get_position(arg[1].value);
		arg[1].value = get_n_byte(4, 0, arg[1].value);
	}
	arg[2].value = get_arg_value(process, &arg[2]);
	position = process->pc + ((arg[1].value + arg[2].value) % IDX_MOD);
	arena.str = g_arena;
	arena.idx = get_position(position);
	write_n_byte(&arena, get_arg_value(process, &arg[0]), get_position, 4);
	(void)game;
}
