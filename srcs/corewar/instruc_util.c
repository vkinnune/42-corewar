/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:08:22 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/04 01:32:57 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	assign_move(t_arg *arg, uint16_t *pos, uint8_t n, uint8_t dir_type)
{
	if (n == DIR_SIZE && dir_type == 1)
		n /= 2;
	arg->value = get_n_byte(n, &g_arena[*pos]);
	*pos = get_position(*pos + n);
}

void	casting(t_process *process, t_arg *arg)
{
	uint8_t	i;

	i = 0;
	while (i < op_tab[process->cmd].arg_amt)
	{
		if (arg[i].arg_type == IND_CODE)
			arg[i].value = (uint16_t)(arg[i].value % IDX_MOD); //recheck this - does every intruction do %
		else if (arg[i].arg_type == DIR_CODE
				&& op_tab[process->cmd].dir_size == 1)
			arg[i].value = (uint16_t)arg[i].value;
		i++;
	}
}

int8_t	assign_arg_value(t_arg *arg, t_process *process)
{
	uint8_t		i;
	int8_t		result;
	uint16_t	pos;

	i = 0;
	pos = get_position(process->prog_counter + 1 + op_tab[process->cmd].arg_byte);
	result = OKEI;
	while (i < op_tab[process->cmd].arg_amt)
	{
		if (arg[i].arg_type == REG_CODE)
		{
			if (g_arena[pos] < r1 || g_arena[pos] > r16)
				result = NOT_OKEI;
			assign_move(&arg[i], &pos, REG_NAME_SIZE, NOT_OKEI);
		}
		else if (arg[i].arg_type == IND_CODE)
			assign_move(&arg[i], &pos, IND_SIZE, NOT_OKEI);
		else if (arg[i].arg_type == DIR_CODE)
			assign_move(&arg[i], &pos, DIR_SIZE, op_tab[process->cmd].dir_size);
		i++;
	}
	if (op_tab[process->cmd].arg_byte == 0)
		process->prog_counter = get_position(pos); //move to next if theres no arg_byte to count
	return (result);
}

int8_t	check_reg(t_process *process, uint8_t cur_2bit, uint8_t arg_type)
{
	if (cur_2bit == REG_CODE)
	{
		process->bytes_to_next += REG_NAME_SIZE;
		if (arg_type & T_REG)
			return (OKEI);
	}
	return (NOT_OKEI);
}

int8_t	check_dir(t_process *process, uint8_t cur_2bit, uint8_t arg_type)
{
	if (cur_2bit == DIR_CODE)
	{
		process->bytes_to_next += DIR_SIZE / (op_tab[process->cmd].dir_size + 1);
		if (arg_type & T_DIR)
			return (OKEI);
	}
	return (NOT_OKEI);
}

int8_t	check_ind(t_process *process, uint8_t cur_2bit, uint8_t arg_type)
{
	if (cur_2bit == IND_CODE)
	{
		process->bytes_to_next += IND_SIZE;
		if (arg_type & T_IND)
			return (OKEI);
	}
	return (NOT_OKEI);
}

int8_t	check_matching_arg(t_process *process, t_arg *arg)
{
	uint8_t		cur_2bit;
	uint8_t		i;
	uint8_t		arg_type;
	int8_t		result;

	i = 0;
	result = OKEI;
	if (op_tab[process->cmd].arg_byte == 0)
		return (OKEI);
	process->bytes_to_next++; //count arg_byte into the total amount
	while (i < op_tab[process->cmd].arg_amt)
	{
		arg_type = op_tab[process->cmd].arg_type[i];
		cur_2bit = get_2bit(g_arena[process->prog_counter + 1], i);
		if ((check_reg(process, cur_2bit, arg_type) == NOT_OKEI)
			&& (check_dir(process, cur_2bit, arg_type) == NOT_OKEI)
			&& (check_ind(process, cur_2bit, arg_type) == NOT_OKEI)) //same as before, +100% readability, +50% line consumption, -25% mental health, -1HP
			result = NOT_OKEI;
		arg[i].arg_type = cur_2bit;
		i++;
	}
	return (result);
}
