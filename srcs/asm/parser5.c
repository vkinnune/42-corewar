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

void	save_token(char **p, char *old_p, t_token_type token_type)
{
	int				size;
	t_token_list	*token_list;
	char			*p_copy;

	p_copy = *p;
	while (*p_copy == ' ' || *p_copy == '\t' || *p_copy == '\n')
		p_copy--;
	size = (p_copy - old_p) + 1;
	token_list = get_token_list();
	token_list->tokens[token_list->token_count].type = token_type;
	token_list->tokens[token_list->token_count].content = ft_memalloc(size);
	ft_memcpy(token_list->tokens[token_list->token_count].content, old_p, size);
	token_list->token_count++;
}

int	direct_check(char **p)
{
	int	i;

	i = 1;
	if (**p == '%')
	{
		if ((*p)[1] == '-')
			i++;
		while (1)
		{
			if (ft_isdigit((*p)[i]))
				i++;
			else if (i == 1)
				break ;
			else
			{
				*p = &(*p)[i - 1];
				get_source()->col += (i - 1);
				return (1);
			}
		}
	}
	return (0);
}

void	parser(char *input)
{
	char	*p;

	p = handle_header(input);
	handle_asm(p);
	free(input);
}

