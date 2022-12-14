/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:47:41 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/05 23:05:20 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static void	handle_arg_byte(int *tk_i, int ins_byte, int op_i)
{
	int				i;
	unsigned char	*a_byte;
	t_token			*toks;
	t_file			*cor;

	toks = get_token_list()->tokens;
	cor = get_core_file();
	i = 0;
	a_byte = &(cor->str[cor->idx++]);
	while (i < g_op_tab[op_i].arg_amt)
	{
		*a_byte |= lab_arg(&toks[*tk_i], ins_byte, i, g_op_tab[op_i].dir_size);
		*a_byte |= dir_arg(&toks[*tk_i], i, g_op_tab[op_i].dir_size);
		*a_byte |= ind_arg(&toks[*tk_i], i);
		*a_byte |= reg_arg(&toks[*tk_i], i);
		i++;
		(*tk_i)++;
		if (*tk_i < get_token_list()->token_count
			&& toks[(*tk_i)].type == separator)
			(*tk_i)++;
	}
}

static void	handle_no_arg(int *tok_i, int ins_byte, int op_i)
{
	t_token	*toks;

	toks = get_token_list()->tokens;
	if (toks[*tok_i].type == direct)
		dir_arg(&toks[*tok_i], 0, g_op_tab[op_i].dir_size);
	else
		lab_arg(&toks[*tok_i], ins_byte, 0, g_op_tab[op_i].dir_size);
	(*tok_i)++;
}

void	handle_instruction(int *tok_i)
{
	int		op_i;
	int		instruction_byte;
	t_token	*tokens;
	t_file	*cor;

	op_i = 0;
	cor = get_core_file();
	tokens = get_token_list()->tokens;
	while (ft_strcmp(tokens[*tok_i].content, g_op_tab[op_i].name))
		op_i++;
	cor->str[cor->idx] = g_op_tab[op_i].order_num;
	instruction_byte = cor->idx++;
	(*tok_i)++;
	if (g_op_tab[op_i].arg_byte)
		handle_arg_byte(tok_i, instruction_byte, op_i);
	else
		handle_no_arg(tok_i, instruction_byte, op_i);
}
