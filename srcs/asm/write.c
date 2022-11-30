/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:20:03 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/30 22:08:45 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void	write_header(void)
{
	t_file	*cor;

	cor = get_core_file();
	cor->idx = 0;
	write_n_byte(cor, 0x00ea83f3, 0, 4);
}

void	write_intro(uint32_t champ_size)
{
	t_source	*wtfisasource;
	t_file		*cor;
	int			i;

	wtfisasource = get_source();
	cor = get_core_file();
	i = 0;
	while (i < PROG_NAME_LENGTH)
		cor->str[cor->idx++] = wtfisasource->name[i++];
	cor->idx += 4;
	write_n_byte(cor, champ_size, 0, 4);
	i = 0;
	while (i < COMMENT_LENGTH)
		cor->str[cor->idx++] = wtfisasource->comment[i++];
	cor->idx += 4;
}

void	write_token(void)
{
	int			tok_idx;
	t_token		*tokens;

	tok_idx = 0;
	get_core_file()->idx = EXEC_CODE_POSITION;
	tokens = get_token_list()->tokens;
	while (tok_idx < get_token_list()->token_count)
	{
		if (tokens[tok_idx].type == instruction)
			handle_instruction(&tok_idx);
		else if (tokens[tok_idx].type == label)
			handle_label(&tok_idx);
		else
			tok_idx++;
	}
}

void	write_label(void)
{
	uint32_t	value;
	t_label_arg	*temp;
	t_label		*label;
	t_file		*cor;

	temp = *get_label_args();
	cor = get_core_file();
	while (temp)
	{
		label = retrieve_label(temp->token->content);
		value = label->idx - temp->instruct_idx;
		cor->idx = temp->map_idx;
		write_n_byte(cor, value, 0, temp->size);
		//free current temp;
		temp = temp->next;
	}
}
