/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:29:55 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/29 16:56:52 by qnguyen          ###   ########.fr       */
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
	return (&get_parser()->token_list);
}

t_label	**get_labels()
{
	return (get_parser()->labels);
}

t_source	*get_source(void)
{
	return (&get_parser()->source);
}

void	init_parser(void)
{
	ft_bzero(get_parser(), sizeof(t_parser));
}
