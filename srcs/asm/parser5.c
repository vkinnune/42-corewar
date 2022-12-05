/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:29:55 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/05 20:16:19 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void	save_token(char **p, char *old_p, t_token_type token_type)
{
	int				size;
	t_token_list	*token_list;
	char			*p_copy;

	p_copy = *p;
	while (*p_copy == ' ' || *p_copy == '%'
		|| *p_copy == '\t' || *p_copy == '\n')
		p_copy--;
	size = (p_copy - old_p) + 1;
	token_list = get_token_list();
	token_list->tokens[token_list->token_count].type = token_type;
	token_list->tokens[token_list->token_count].content
		= ft_memalloc(size * 10);
	check_err_malloc(token_list->tokens[token_list->token_count].content);
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

t_file	*get_core_file(void)
{
	static t_file	cor;

	return (&cor);
}

void	token_check(void)
{
	int				i;
	t_token_list	*token_list;

	i = 0;
	token_list = get_token_list();
	while (check_instruction(&i, token_list))
	{
	}
	label_list_error();
	if (token_list->token_count == 0
		|| get_source()->is_instructions == false)
		ft_out("Error: No tokens");
}
