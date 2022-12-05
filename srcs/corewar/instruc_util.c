/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:08:22 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/01 19:05:39 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int32_t	get_arg_value(t_process *process, t_arg *arg) //replaced casting with individual value transformer when they are called
{
	if (arg->type == REG_CODE)
		return (process->reg[arg->value]);
	else if (arg->type == IND_CODE)
		return ((int16_t)(process->pc + ((int16_t)arg->value % IDX_MOD)));
	else if (op_tab[process->cmd].dir_size == 1)
		return ((int16_t)arg->value);
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
int8_t	check_matching_arg(t_process *process, t_arg *arg)
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
		if (!check_reg(process, cur_2bit, op_arg_type, &arg[i])
			&& !check_dir(process, cur_2bit, op_arg_type, &arg[i])
			&& !check_ind(process, cur_2bit, op_arg_type, &arg[i])) //same as before, +100% readability, +50% line consumption, -25% mental health, -1HP
			result = NOT_OKEI;
		i++;
	}
	return (result);
}

uint16_t	get_position(uint16_t pos)
{
	if (pos < 4096)
		return (pos);
	return (pos % MEM_SIZE);
}
