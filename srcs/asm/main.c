/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:29:55 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/07 16:37:04 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	find_ins(char *content)
{
	int	ins;
	int	size;

	ins = 0;
	size = ft_strlen(content);
	while (ins != INSTRUCTION_AMOUNT)
	{
		if (!ft_strncmp(op_tab[ins].name, content, size))
			return (ins);
		ins++;
	}
	ft_out("ERROR");
	return (-1);
}

int	check_instruction(int *i, t_token_list *token_list)
{
	int	ins;
	int	arg;

	ins = 0;
	arg = 0;
	if (!token_list->tokens[*i].content)
		return (0);
	if (token_list->tokens[*i].type == label)
		(*i)++;
	if (token_list->tokens[*i].type != instruction)
		ft_out("ERRRORRR");
	ins = find_ins(token_list->tokens[*i].content);
	(*i)++;
	while (1)
	{
		token_list->tokens[*i].content; //check that is correct argument
		(*i)++;
		arg++;
		if (arg == op_tab[ins].arg_amt)
			break ;
		else if (token_list->tokens[*i].type == separator)
			(*i)++;
		else
			ft_out("ERROR ON SEPERATOR");
	}
	op_tab[ins].arg_type[0];
	return (1);
}

void	token_check()
{
	t_token_list	*token_list;
	int		i;

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

