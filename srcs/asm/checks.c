/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:29:55 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/29 11:46:21 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

int	find_ins(char *content)
{
	int	ins;
	int	size;

	ins = 0;
	size = ft_strlen(content);
	while (ins != INSTRUCTION_AMOUNT)
	{
		if (!ft_strncmp(op_tab[ins].name, content, size)) //why not strcmp
			return (ins);
		ins++;
	}
	ft_out("ERROR");
	return (-1);
}

int	check_token_args(t_token_type type, int ins, int arg)
{
	uint8_t	arg_type;

	if (type == direct || type == direct_label)
		arg_type = T_DIR;
	else if (type == indirect || type == indirect_label)
		arg_type = T_IND;
	else if (type == reg)
		arg_type = T_REG;
	if (!(op_tab[ins].arg_type[arg] & arg_type))
		return (0);
	return (1);
}

int	check_instruction(int *i, t_token_list *token_list) // in need of some mad refactoring
{														// why is this taking token_list when all it does is to point to tokens?
	int	ins;											// ->try passing tokens
	int	arg;

	ins = 0;
	arg = 0;
	if (!token_list->tokens[*i].content)
		return (0);
	if (token_list->tokens[*i].type == label || token_list->tokens[*i].type == direct_label)
	{
		add_label_list(token_list->tokens[*i].content, token_list->tokens[*i].type);
		(*i)++;
	}
	if (token_list->tokens[*i].type != instruction)
		return (1);
	ins = find_ins(token_list->tokens[*i].content);
	(*i)++;
	while (arg != op_tab[ins].arg_amt)
	{
		if (!check_token_args(token_list->tokens[*i].type, ins, arg)) //check that is correct argument
			ft_out("ERROR ON ARGS");
		(*i)++;
		arg++;
		if (token_list->tokens[*i].type == separator)
			(*i)++;
		else if (arg != op_tab[ins].arg_amt)
			ft_out("ERROR ON SEPERATOR");
	}
	return (1);
}

void	token_check()
{
	t_token_list	*token_list;
	int		i;

	i = 0;
	token_list = get_token_list();
	while (check_instruction(&i, token_list));
	label_list_error();
}
