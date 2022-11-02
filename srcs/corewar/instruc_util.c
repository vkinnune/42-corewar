/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:08:22 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/02 16:47:58 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

uint8_t	check_reg_value(uint8_t *arg, uint8_t arg_num, uint16_t arena_pos, uint8_t cmd)
{
	uint8_t	i;
	uint8_t	reg_pos;

	i = 0;
	reg_pos = arena_pos;
	while (i < arg_num)
	{
		if (arg[i] == REG_CODE)
			reg_pos += REG_NAME_SIZE;
		else if (arg[i] == IND_CODE)
			reg_pos += IND_SIZE;
		else if (arg[i] == DIR_CODE)
			reg_pos += DIR_SIZE / (op_tab[cmd].small_dir + 1);
		i++;
	}
	if (g_arena[reg_pos] >= r1 && g_arena[reg_pos] <= r16)
		return (DAIJOBU);
	return (EI_KIITOS);
}

uint8_t	check_matching_arg(t_process *process, uint8_t *arg)
{
	uint8_t		cur_2bit;
	uint8_t		arg_byte;
	uint8_t		i;
	uint8_t		cmd;
	uint16_t	type_pos;

	cmd = process->instruction - 1;
	type_pos = process->prog_counter + 1;
	arg_byte = g_arena[type_pos];
	// arg_byte = 0b01101100; //for testing if IND_CODE is present in the arg_type but op_tab takes only T_DIR | T_REG
	// ft_printf("%08b\n", arg_byte);
	i = 0;
	while (i < op_tab[cmd].arg_amt)
	{
		cur_2bit = get_2bit(arg_byte, i);
		if ((cur_2bit == REG_CODE && op_tab[cmd].arg_type[i] & T_REG)
			|| (cur_2bit == DIR_CODE && op_tab[cmd].arg_type[i] & T_DIR)
			|| (cur_2bit == IND_CODE && op_tab[cmd].arg_type[i] & T_IND)) //same as before, +100% readability, +50% line consumption, -25% mental health, -1HP
			{
				if (cur_2bit == REG_CODE)
					check_reg_value(arg, i + 1, type_pos + 1, cmd);
				arg[i] = cur_2bit;
			}
		else
			return (EI_KIITOS);
		i++;
	}
	return (DAIJOBU);
}
