/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:29:55 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/30 23:05:45 by qnguyen          ###   ########.fr       */
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
		if (!ft_strncmp(op_tab[ins].name, content, size))
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

int	check_and_handle_labolz(t_token_list *toks, int *i)
{
	if (toks->tokens[*i].type == label || toks->tokens[*i].type == direct_label
		|| toks->tokens[*i].type == indirect_label)
	{
		add_label_list(toks->tokens[*i].content,
			toks->tokens[*i].type);
		(*i)++;
		return (1);
	}
	return (0);
}

//????
int	more_check_instruction(int *i, t_token_list *token_list)
{
	if (!token_list->tokens[*i].content)
		return (0);
	check_and_handle_labolz(token_list, i);
	if (token_list->tokens[*i].type != instruction)
		return (1);
	return (2);
}

//????
int	check_instruction(int *i, t_token_list *token_list)
{
	int	ins;
	int	ret;
	int	arg;

	ins = 0;
	arg = 0;
	ret = more_check_instruction(i, token_list);
	if (ret == 1)
		return (1);
	else if (ret == 0)
		return (0);
	ins = find_ins(token_list->tokens[*i].content);
	(*i)++;
	while (arg != op_tab[ins].arg_amt)
	{
		if (!check_token_args(token_list->tokens[*i].type, ins, arg))
			ft_out("ERROR ON ARGS");
		if (!check_and_handle_labolz(token_list, i))
			(*i)++;
		arg++;
		if (token_list->tokens[*i].type == separator)
			(*i)++;
		else if (arg != op_tab[ins].arg_amt)
			ft_out("ERROR ON SEPERATOR");
	}
	return (1);
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
}
