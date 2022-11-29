/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:47:41 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/28 17:43:42 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

uint8_t	lab_arg(t_file *cor, int arg_i, int op_size, char *content)
{
	//save current token idx, dir_size, and cor.idx to an label_args array
	//return (DIR || IND _CODE);
	return (0);
}

uint8_t	dir_arg(t_file *cor, int arg_i, int op_size, char *content)
{
	uint8_t	dir_size;

	dir_size = DIR_SIZE / (1 + op_size);
	write_n_byte(cor, ft_atoi(&content[1]), 0, dir_size);
	return (DIR_CODE << (2 * (3 - arg_i)));
}

uint8_t	ind_arg(t_file *cor, int arg_i, int op_size, char *content)
{
	write_n_byte(cor, (uint16_t)ft_atoi(&content[0]), 0, IND_SIZE);
	return (IND_CODE << (2 * (3 - arg_i)));
}

uint8_t	reg_arg(t_file *cor, int arg_i, int op_size, char *content)
{
	write_n_byte(cor, (uint8_t)ft_atoi(&content[1]), 0, REG_NAME_SIZE);
	return (REG_CODE << (2 * (3 - arg_i)));
}

void	handle_arg_byte(t_file *cor, int op_i, int *tok_idx)
{
	int				arg_i;
	unsigned char	*a_byte;
	t_token			*toks;

	toks = get_token_list()->tokens;
	arg_i = 0;
	a_byte = &(cor->str[cor->idx++]);
	while (arg_i < op_tab[op_i].arg_amt)
	{
		if (toks[*tok_idx].type == direct)
			*a_byte |= dir_arg(cor, arg_i,
					op_tab[op_i].dir_size, toks[*tok_idx].content);
		else if (toks[*tok_idx].type == indirect)
			*a_byte |= ind_arg(cor, arg_i, op_tab[op_i].dir_size, toks[*tok_idx].content);
		else if (toks[*tok_idx].type == reg)
			*a_byte |= reg_arg(cor, arg_i, op_tab[op_i].dir_size, toks[*tok_idx].content);
		else if (toks[*tok_idx].type == direct_label)
			//|| toks[*tok_idx].type == ind_label
			lab_arg(cor, arg_i,
				op_tab[op_i].dir_size, toks[*tok_idx].content);
		arg_i++;
		(*tok_idx) += 1 + (*tok_idx < get_token_list()->token_count
				&& toks[(*tok_idx) + 1].type == separator);
	}
}

void	handle_instruction(t_file *cor, int *tok_idx)
{
	int		op_idx;
	t_token	*tokens;

	op_idx = 0;
	tokens = get_token_list()->tokens;
	while (ft_strcmp(tokens[*tok_idx].content, op_tab[op_idx].name))
		op_idx++;
	cor->str[cor->idx++] = op_tab[op_idx].order_num;
	(*tok_idx)++;
	if (op_tab[op_idx].arg_byte)
		handle_arg_byte(cor, op_idx, tok_idx);
	else
		dir_arg(cor, 0, op_tab[op_idx].dir_size, tokens[*tok_idx].content);
}
