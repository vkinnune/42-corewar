/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:08:22 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/02 19:30:46 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	assign_and_move(t_arg *arg, uint8_t *pos, uint8_t value, uint8_t dir_type)
{	//try and check dir_type from op_tab with cmd
	if (value == DIR_SIZE && dir_type == 1)
		value /= 2;
	arg->value = get_n_byte(value, &g_arena[*pos]);
	*pos += value; //move the right ammount
}

int8_t	assign_arg_value(t_arg *arg, t_process *process)
{
	uint8_t	i;
	uint8_t	pos;
	uint8_t cmd;

	i = 0;
	pos = process->prog_counter + 2;
	cmd = process->instruction - 1;
	while (i < op_tab[cmd].arg_amt)
	{
		if (arg[i].arg_type == REG_CODE)
			assign_and_move(&arg[i], &pos, REG_NAME_SIZE, EI_KIITOS);
		else if (arg[i].arg_type == IND_CODE)
			assign_and_move(&arg[i], &pos, IND_SIZE, EI_KIITOS);
		else if (arg[i].arg_type == DIR_CODE)
			assign_and_move(&arg[i], &pos, DIR_SIZE, op_tab[cmd].small_dir);
		i++;
	}
	if (g_arena[pos] >= r1 && g_arena[pos] <= r16)
		return (pos);
	return (EI_KIITOS);
}

uint8_t	check_matching_arg(t_process *process, t_arg *arg)
{
	uint8_t		cur_2bit;
	uint8_t		i;
	uint8_t		cmd;
	uint8_t		arg_byte;
	uint16_t	arg_byte_pos;

	cmd = process->instruction - 1;
	arg_byte_pos = process->prog_counter + 1;
	arg_byte = g_arena[arg_byte_pos];
	i = 0;
	while (i < op_tab[cmd].arg_amt)
	{
		cur_2bit = get_2bit(arg_byte, i);
		if ((cur_2bit == REG_CODE && op_tab[cmd].arg_type[i] & T_REG)
			|| (cur_2bit == DIR_CODE && op_tab[cmd].arg_type[i] & T_DIR)
			|| (cur_2bit == IND_CODE && op_tab[cmd].arg_type[i] & T_IND)) //same as before, +100% readability, +50% line consumption, -25% mental health, -1HP
				arg[i].arg_type = cur_2bit;
		else
			return (EI_KIITOS);
		i++;
	}
	return (DAIJOBU);
}

void	casting(t_arg *arg)
{
	uint8_t	i;

	i = 0;
	while (i < op_tab[10].arg_amt)
	{
		if (arg[i].arg_type == IND_CODE)
			arg[i].value = (uint16_t)(arg[i].value % IDX_MOD);
		else if (arg[i].arg_type == DIR_CODE && op_tab[10].small_dir == 1)
			arg[i].value = (uint16_t)arg[i].value;
		i++;
	}
}
