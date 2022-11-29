/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:29:55 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/28 18:12:39 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

t_parser	*get_parser(void)
{
	static t_parser	parse;

	return (&parse);
}

t_token_list	*get_token_list(void)
{
	t_parser	*parse;

	parse = get_parser();
	return (&parse->token_list);
}

t_label_list	*get_label_list(void)
{
	t_parser	*parse;

	parse = get_parser();
	return (&parse->label_list);
}

t_source	*get_source(void)
{
	t_parser	*parse;

	parse = get_parser();
	return (&parse->source);
}

void	init_parser(void)
{
	t_parser	*parse;

	parse = get_parser();
	ft_bzero(parse, sizeof(t_parser));
}

