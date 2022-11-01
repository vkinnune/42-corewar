/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:53:47 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/01 20:02:44 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	check_matching_arg(t_process *process)
{
	uint8_t	cur_2bit;
	uint8_t	byte;
	uint8_t	i;
	uint8_t	cmd_idx;

	cmd_idx = process->instruction - 1;
	byte = g_arena[process->prog_counter + 1];
	//byte = 0b01101100; //for testing if IND_CODE is present in the arg_type but op_tab takes only T_DIR | T_REG
	ft_printf("%08b\n", byte);
	i = 0;
	while (i < op_tab[cmd_idx].arg_amt)
	{
		cur_2bit = get_2bit(byte, i);
		if ((cur_2bit != IND_CODE && cur_2bit & op_tab[cmd_idx].arg_type[i])
			|| (op_tab[cmd_idx].arg_type[i] & 0b100))
			ft_printf("%02b arg: correct\n", cur_2bit);
		i++;
	}
	//save arg type for later usage
}

void	sti(t_process *process)
{

}
