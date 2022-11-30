/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:29:55 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/30 21:34:10 by qnguyen          ###   ########.fr       */
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

t_label	**get_labels(void)
{
	return (get_parser()->labels);
}

t_source	*get_source(void)
{
	return (&get_parser()->source);
}

t_label_arg	**get_label_args(void)
{
	static t_label_arg	*label_args;

	return (&label_args);
}

t_file	*get_core_file(void)
{
	static t_file	cor;

	return (&cor);
}
