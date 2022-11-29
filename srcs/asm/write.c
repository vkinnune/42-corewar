/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:20:03 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/29 19:10:07 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void	write_header(void)
{
	write_n_byte(get_core_file(), 0x00ea83f3, 0, 4);
}

void	write_intro(void)
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
	//execcode
	cor->idx += 4;
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
