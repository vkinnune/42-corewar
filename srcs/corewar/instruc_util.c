/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:08:22 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/17 17:18:26 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

uint32_t	get_arg_value(t_process *process, t_arg *arg) //replaced casting with individual value transformer when they are called
{
	if (arg->type == REG_CODE)
		return (process->reg[arg->value]);
	else if (arg->type == IND_CODE)
		return ((uint16_t)(process->pc + ((int16_t)arg->value % IDX_MOD)));
	else if (op_tab[process->cmd].dir_size == 1)
		return ((uint16_t)arg->value);
	return (arg->value);
}

int8_t	check_reg(t_process *process, uint8_t cur_2bit, uint8_t arg_type, t_arg *arg)
{
	uint16_t	pos;

	if (cur_2bit != REG_CODE)
		return (NOT_OKEI);
	pos = get_position(process->pc + process->bytes_to_next);
	arg->value = get_n_byte(REG_NAME_SIZE, 0, pos);
	process->bytes_to_next += REG_NAME_SIZE;
	if (!(arg_type & T_REG))
		return (NOT_OKEI);
	if (arg->value < r1 || arg->value > r16)
		return (NOT_OKEI);
	arg->type = cur_2bit;
	return (OKEI);

}

int8_t	check_dir(t_process *process, uint8_t cur_2bit, uint8_t arg_type, t_arg *arg)
{
	uint8_t		byte_ammount;
	uint16_t	pos;

	if (cur_2bit != DIR_CODE)
		return (NOT_OKEI);
	byte_ammount = DIR_SIZE / (op_tab[process->cmd].dir_size + 1);
	pos = get_position(process->pc + process->bytes_to_next);
	arg->value = get_n_byte(byte_ammount, 0, pos);
	process->bytes_to_next += byte_ammount;
	if (!(arg_type & T_DIR))
		return (NOT_OKEI);
	arg->type = cur_2bit;
	return (OKEI);
}

int8_t	check_ind(t_process *process, uint8_t cur_2bit, uint8_t arg_type, t_arg *arg)
{
	uint16_t	pos;

	if (cur_2bit != IND_CODE)
		return (NOT_OKEI);
	pos = get_position(process->pc + process->bytes_to_next);
	arg->value = get_n_byte(IND_SIZE, 0, pos);
	process->bytes_to_next += IND_SIZE;
	if (!(arg_type & T_IND))
		return (NOT_OKEI);
	arg->type = cur_2bit;
	return (OKEI);
}

//how do we clean the 3 check_arg function above
int8_t	check_matching_arg(t_process *process, t_arg *arg, t_game_param *game)
{
	uint8_t		cur_2bit;
	uint8_t		i;
	uint8_t		op_arg_type;
	int8_t		result;

	i = 0;
	result = OKEI;
	if (op_tab[process->cmd].arg_byte == 0)
		return (OKEI);
	process->bytes_to_next++; //count arg_byte into the total amount
	while (i < op_tab[process->cmd].arg_amt)
	{
		op_arg_type = op_tab[process->cmd].arg_type[i];
		cur_2bit = get_2bit(g_arena[get_position(process->pc + 1)], i);
/* 		if (game->current_cycle == 13856 && process->id + 1 == 1026 && process->cmd == 2)
		{
			ft_printf("\tpos: %d\n", get_position(process->pc + 1));
			ft_printf("\t\tc2b: %02b\n", cur_2bit);
		} */
		if (!check_reg(process, cur_2bit, op_arg_type, &arg[i])
			&& !check_dir(process, cur_2bit, op_arg_type, &arg[i])
			&& !check_ind(process, cur_2bit, op_arg_type, &arg[i])) //same as before, +100% readability, +50% line consumption, -25% mental health, -1HP
			result = NOT_OKEI;
/* 		if (game->current_cycle == 13856 && process->id + 1 == 1026 && process->cmd == 2)
			ft_printf("\t\targ: %d\n", arg[i].value); */
		i++;
	}
	return (result);
}

//write value of arg to g_arena[position]
void	write_4byte(t_process *process, uint32_t value, uint16_t position)
{
	uint8_t	i;

	i = 0;
	while (i < 4)
	{
		g_arena[get_position(position + i)] = get_2hext(value, i);
		i++;
	}
}

uint16_t	get_position(uint16_t pos)
{
	if (pos < 4096)
		return (pos);
	return (pos % MEM_SIZE);
}
