/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:20:03 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/27 19:46:27 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void	write_header(t_file *cor)
{
	write_n_byte(cor, 0x00ea83f3, 0, 4);
}

void	write_intro(t_file *cor)
{
	t_source	*wtfisasource;
	int			i;

	wtfisasource = get_source();
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

void	write_token(t_file *cor)
{
	int			tok_idx;
	t_token		*tokens;

	tok_idx = 0;
	tokens = get_token_list()->tokens;
	while (tok_idx < get_token_list()->token_count)
	{
		if (tokens[tok_idx].type == instruction)
			handle_instruction(cor, &tok_idx);
		else if (tokens[tok_idx].type == label)
			handle_label(cor, &tok_idx);
		else
			tok_idx++;
	}
}
