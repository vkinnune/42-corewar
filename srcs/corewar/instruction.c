/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:53:47 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/05 16:46:25 by jrummuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	live(t_process *process, t_arg *arg, t_game_param *game)
{
	process->bytes_to_next += DIR_SIZE;
	process->last_live_cycle = game->current_cycle;
	game->live_performed++;
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
}

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
}

void	zjmp(t_process *process, t_arg *arg, t_game_param *game)
{
	int32_t	position;
	int		i;

	position = process->pc + ((int16_t)arg[0].value % IDX_MOD);
	position = get_position(position);
	process->bytes_to_next += 2;
	if (process->carry == 1)
	{
		process->bytes_to_next = 0;
		process->pc = position;
	}
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
}

void	l_foork(t_process *process, t_arg *arg, t_game_param *game)
{
	uint8_t		i;
	t_process	*new;
	int32_t		position;

	if (process->cmd == 11)
		position = process->pc + (int16_t)arg[0].value % IDX_MOD;
	else
		position = process->pc + (int16_t)arg[0].value;
	position = get_position(position);
	new = new_process(game->head, position, -process->reg[r1]);
	i = 0;
	while (++i <= r16)
		new->reg[i] = process->reg[i];
	new->carry = process->carry;
	new->last_live_cycle = process->last_live_cycle;
	new->cmd = -1;
	process->bytes_to_next += DIR_SIZE / 2;
	game->head = new;
}

void	aff(t_process *process, t_arg *arg, t_game_param *game)
{
	char	a;

	if (g_flags.aff == SET)
	{
		a = (char)get_arg_value(process, &arg[0]);
		ft_printf("Aff: %c\n", a);
	}
}
