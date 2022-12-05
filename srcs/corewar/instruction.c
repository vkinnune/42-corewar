/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:53:47 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/05 17:49:35 by jrummuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	live(t_process *process, t_arg *arg, t_game_param *game)
{
	process->bytes_to_next += DIR_SIZE;
	process->last_live_cycle = game->current_cycle;
	game->live_performed++;
	(void)arg;
}

void	ld(t_process *process, t_arg *arg, t_game_param *game)
{
	arg[0].value = get_arg_value(process, &arg[0]);
	if (arg[0].type == IND_CODE)
	{
		arg[0].value = get_position(arg[0].value);
		arg[0].value = get_n_byte(4, 0, arg[0].value);
	}
	process->reg[arg[1].value] = arg[0].value;
	process->carry = (process->reg[arg[1].value] == 0);
	(void)game;
}

void	lld(t_process *process, t_arg *arg, t_game_param *game)
{
	if (arg[0].type == IND_CODE)
		arg[0].value = process->pc + (int16_t)(arg[0].value);
	else
		arg[0].value = get_arg_value(process, &arg[0]);
	if (arg[0].type == IND_CODE)
	{
		arg[0].value = get_position(arg[0].value);
		arg[0].value = (int16_t)get_n_byte(2, 0, arg[0].value);
	}
	process->reg[arg[1].value] = arg[0].value;
	process->carry = (process->reg[arg[1].value] == 0);
	(void)game;
}

void	st(t_process *process, t_arg *arg, t_game_param *game)
{
	int32_t	arg0;
	int32_t	arg1;
	t_file	arena;

	arg0 = get_arg_value(process, &arg[0]);
	if (arg[1].type == IND_CODE)
	{
		arg1 = get_arg_value(process, &arg[1]);
		arena.str = g_arena;
		arena.idx = get_position(arg1);
		write_n_byte(&arena, arg0, get_position, 4);
	}
	else
		process->reg[arg[1].value] = arg0;
	(void)game;
}

void	add_sub(t_process *process, t_arg *arg, t_game_param *game)
{
	int32_t	arg0;
	int32_t	arg1;

	arg0 = get_arg_value(process, &arg[0]);
	arg1 = get_arg_value(process, &arg[1]);
	if (process->cmd == 3)
		process->reg[arg[2].value] = arg0 + arg1;
	else
		process->reg[arg[2].value] = arg0 - arg1;
	process->carry = (process->reg[arg[2].value] == 0);
	(void)game;
}
