/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:53:47 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/02 14:17:30 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

uint8_t	check_matching_arg(t_process *process, uint8_t *arg)
{
	uint8_t	cur_2bit;
	uint8_t	byte;
	uint8_t	i;
	uint8_t	cmd_idx;

	cmd_idx = process->instruction - 1;
	byte = g_arena[process->prog_counter + 1];
	// byte = 0b01101100; //for testing if IND_CODE is present in the arg_type but op_tab takes only T_DIR | T_REG
	// ft_printf("%08b\n", byte);
	i = 0;
	while (i < op_tab[cmd_idx].arg_amt)
	{
		cur_2bit = get_2bit(byte, i);
		if ((cur_2bit == REG_CODE && op_tab[cmd_idx].arg_type[i] & T_REG)
			|| (cur_2bit == DIR_CODE && op_tab[cmd_idx].arg_type[i] & T_DIR)
			|| (cur_2bit == IND_CODE && op_tab[cmd_idx].arg_type[i] & T_IND)) //same as before, +100% readability, +50% line consumption, -25% mental health, -1HP
			arg[i] = cur_2bit;
		else
			return (EI_KIITOS);
		i++;
	}
	return (DAIJOBU);
}

void	sti(t_process *process)
{
	uint8_t	arg[3];

	if (check_matching_arg(process, arg) != DAIJOBU)
	{
		ft_printf("$rdame dayo$d\n");
		return;
	}
	ft_printf("$gdaijobu da$d\n");
}
