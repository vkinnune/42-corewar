/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:48:56 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/27 19:35:28 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void	handle_label(t_file *cor, int *tok_idx)
{
/* 	t_token	*tokens;

	tokens = get_token_list()->tokens;
	save current cor.idx to hash table
	ft_printf("label found: %s @%d\n", tokens[*tok_idx].content, cor->idx); */
	(*tok_idx)++;
}
