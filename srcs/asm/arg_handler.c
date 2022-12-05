/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:48:21 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/05 18:47:26 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

uint8_t	ind_lab_arg(t_token *toks, int instr_idx, int arg_i)
{
	uint8_t	size;

	size = IND_SIZE;
	add_l_arg(toks, instr_idx, size);
	get_core_file()->idx += size;
	return (IND_CODE << (2 * (3 - arg_i)));
}

uint8_t	lab_arg(t_token *toks, int instr_idx, int arg_i, int op_size)
{
	uint8_t	size;

	if (toks->type == indirect_label)
		return (ind_lab_arg(toks, instr_idx, arg_i));
	else if (toks->type != direct_label)
		return (0);
	size = DIR_SIZE / (1 + op_size);
	add_l_arg(toks, instr_idx, size);
	get_core_file()->idx += size;
	return (DIR_CODE << (2 * (3 - arg_i)));
}

uint8_t	dir_arg(t_token *toks, int arg_i, int op_size)
{
	uint8_t		dir_size;
	uint32_t	value;
	t_file		*cor;

	if (toks->type != direct)
		return (0);
	cor = get_core_file();
	value = ft_atoi(&toks->content[1]);
	dir_size = DIR_SIZE / (1 + op_size);
	write_n_byte(cor, value, 0, dir_size);
	return (DIR_CODE << (2 * (3 - arg_i)));
}

uint8_t	ind_arg(t_token *toks, int arg_i)
{
	uint16_t	value;
	t_file		*cor;

	if (toks->type != indirect)
		return (0);
	cor = get_core_file();
	value = (uint16_t)ft_atoi(&toks->content[0]);
	write_n_byte(cor, value, 0, IND_SIZE);
	return (IND_CODE << (2 * (3 - arg_i)));
}

uint8_t	reg_arg(t_token *toks, int arg_i)
{
	uint8_t	value;
	t_file	*cor;

	if (toks->type != reg)
		return (0);
	cor = get_core_file();
	value = (uint8_t)ft_atoi(&toks->content[1]);
	write_n_byte(cor, value, 0, REG_NAME_SIZE);
	return (REG_CODE << (2 * (3 - arg_i)));
}
