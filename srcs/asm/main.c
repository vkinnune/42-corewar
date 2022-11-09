/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:29:55 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/09 16:06:44 by vkinnune         ###   ########.fr       */
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
	if (token_list->tokens[*i].type == label)
		(*i)++;
	if (token_list->tokens[*i].type != instruction)
		return (0);
	ins = find_ins(token_list->tokens[*i].content);
	(*i)++;
	while (arg != op_tab[ins].arg_amt)
	{
		token_list->tokens[*i + arg].content; //check that is correct argument
		arg++;
		if (token_list->tokens[*i + arg].type == separator)
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

unsigned int	generate_id(char *content)
{
	unsigned int	res;
	int	size;
	int	i;

	size = ft_strlen(content);
	i = 0;
	while (i != size)
	{
		res = res * 42 + content[i];
		i++;
	}
	return (res);
}

void	add_label_list(char *content, t_token_type token_type)
{
	t_label_list	*label_list;
	int			i;
	unsigned int			id;

	id = generate_id(content);
	label_list = get_label_list();
	i = 0;
	while (i != label_list->label_count)
	{
		if (label_list->labels[i].id == id)
			break;
		i++;
	}
	if (i == label_list->label_count)
		label_list->labels[label_list->label_count++].id = id;
}

void	label_list_check()
{
	t_token_list	*token_list;
	int				i;

	token_list = get_token_list();
	i = 0;
	while (i != token_list->token_count)
	{
		if (token_list->tokens[i].type == label || token_list->tokens[i].type == direct_label)
			add_label_list(token_list->tokens[i].content, token_list->tokens[i].type);
		i++;
	}
}

int	main(int ac, char **av)
{
	init_parser();
	validate_argument(ac, av);
	parser(read_file(av[1]));
	print_tokens();
	token_check();
	label_list_check();
	return (0);
}

