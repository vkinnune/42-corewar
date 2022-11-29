/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:47:41 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/29 19:29:54 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

uint8_t	lab_arg(int instr_idx, int arg_i, int op_size, t_token *toks)
{
	uint8_t		size;
	t_file		*cor;
	t_label_arg	*new;
	t_label_arg	**head;

	if (toks->type != direct_label && toks->type != indirect_label)
		return (0);
	cor = get_core_file();
	if (toks->type == direct_label)
		size = DIR_SIZE / (1 + op_size);
	else
		size = IND_SIZE;
	head = get_label_args();
	new = new_l_arg(toks, cor->idx, instr_idx, size);
	new->next = *head;
	*head = new;
	//return (DIR || IND _CODE);
	return (0); //for now
}

uint8_t	dir_arg(int arg_i, int op_size, t_token *toks)
{
	t_file			*cor;
	uint8_t	dir_size;

	if (toks->type != direct)
		return (0);
	cor = get_core_file();
	dir_size = DIR_SIZE / (1 + op_size);
	write_n_byte(cor, ft_atoi(&toks->content[1]), 0, dir_size);
	return (DIR_CODE << (2 * (3 - arg_i)));
}

uint8_t	ind_arg(int arg_i, t_token *toks)
{
	t_file			*cor;

	if (toks->type != indirect)
		return (0);
	cor = get_core_file();
	write_n_byte(cor, (uint16_t)ft_atoi(&toks->content[0]), 0, IND_SIZE);
	return (IND_CODE << (2 * (3 - arg_i)));
}

uint8_t	reg_arg(int arg_i, t_token *toks)
{
	t_file			*cor;

	cor = get_core_file();
	write_n_byte(cor, (uint8_t)ft_atoi(&toks->content[1]), 0, REG_NAME_SIZE);
	return (REG_CODE << (2 * (3 - arg_i)));
}

void	handle_arg_byte(int op_i, int *tok_i)
{
	int				i;
	int				ins_byte;
	unsigned char	*a_byte;
	t_token			*toks;
	t_file			*cor;

	toks = get_token_list()->tokens;
	cor = get_core_file();
	i = 0;
	ins_byte = cor->idx++;
	a_byte = &(cor->str[cor->idx++]);
	while (i < op_tab[op_i].arg_amt)
	{
		*a_byte |= lab_arg(ins_byte, i, op_tab[op_i].dir_size, &toks[*tok_i]);
		*a_byte |= dir_arg(i, op_tab[op_i].dir_size, &toks[*tok_i]);
		*a_byte |= ind_arg(i, &toks[*tok_i]);
		*a_byte |= reg_arg(i, &toks[*tok_i]);
		i++;
		(*tok_i) += 1 + (*tok_i < get_token_list()->token_count
				&& toks[(*tok_i) + 1].type == separator);
	}
}

void	handle_instruction(int *tok_idx)
{
	int		op_idx;
	t_token	*tokens;
	t_file	*cor;

	op_idx = 0;
	cor = get_core_file();
	tokens = get_token_list()->tokens;
	while (ft_strcmp(tokens[*tok_idx].content, op_tab[op_idx].name))
		op_idx++;
	cor->str[cor->idx] = op_tab[op_idx].order_num;
	(*tok_idx)++;
	if (op_tab[op_idx].arg_byte)
		handle_arg_byte(op_idx, tok_idx);
	else // or label
		dir_arg(0, op_tab[op_idx].dir_size, &tokens[*tok_idx]);
}
