/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:29:55 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/07 16:00:58 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	find_ins(char *content)
{
	int	ins;

	ins = 0;
	while (ins != INSTRUCTION_AMOUNT)
	{
		if (!ft_strncmp(op_tab[ins].name, content, ft_strlen(op_tab[ins].name)))
			return (1);
		ins++;
	}
	return (ins);
}

int	check_instruction(int *i, t_token_list *token_list)
{
	int	ins;

	ins = 0;
	if (token_list->tokens[*i].type == label)
		(*i)++;
	if (token_list->tokens[*i].type != instruction)
		return (0);
	ins = find_ins(token_list);
	return (1);
}

void	token_check()
{
	t_token_list	*token_list;
	int				i;

	i = 0;
	token_list = get_token_list();
	while (check_instruction(&i, token_list));
}

int	main(int ac, char **av)
{
	init_parser();
	validate_argument(ac, av);
	parser(read_file(av[1]));
	print_tokens();
	token_check();
	return (0);
}

