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

char	*get_name(char *argc)
{
	int	len;
	int	name_len;
	char	*name;

	len = ft_strlen(argc);
	while (len)
	{
		if (argc[len] == '.')
			break ;
		len--;
	}
	name_len = &argc[len] - argc;
	name = ft_memalloc(name_len + 5);
	ft_memcpy(name, argc, name_len);
	ft_memcpy(&name[name_len], ".cor", 5);
	return (name);
}

void	handle_arg_byte(char *str, int *str_idx, int op_idx, int *tok_idx)
{
	int				arg_idx;
	t_token			*token;

	token = get_token_list()->tokens;
	str[*str_idx] = 0;
	(*tok_idx)++;
	arg_idx = 0;
	if (op_tab[op_idx].arg_byte)
	{
		while (arg_idx < op_tab[op_idx].arg_amt)
		{
			if (token[*tok_idx].type == direct)
				str[*str_idx] = (str[*str_idx] + DIR_CODE) << (2 * (3 - arg_idx));
			else if (token[*tok_idx].type == indirect)
				str[*str_idx] = (str[*str_idx] + IND_CODE) << (2 * (3 - arg_idx));
			else if (token[*tok_idx].type == reg)
				str[*str_idx] = (str[*str_idx] + REG_CODE) << (2 * (3 - arg_idx));
			//assign each arg to str
			arg_idx++;
			(*tok_idx)++;
		}
		(*str_idx)++;
	}
	else
	{
		//assign dir
		(*tok_idx)++;
	}
}

int	handle_instruction(char *str, int *str_idx, int *tok_idx)
{
	int	op_idx;
	int amount;
	t_token	*token;

	op_idx = 0;
	op_idx = 0;
	token = get_token_list()->tokens;
	while(op_idx != 17)
	{
		if (!ft_strcmp(token[*tok_idx].content, op_tab[op_idx].name))
		{
			str[(*str_idx)++] = op_tab[op_idx].order_num;
			handle_arg_byte(str, str_idx, op_idx, tok_idx);
			return 0;
		}
		op_idx++;
	}
	return (0);
}

void	things_into_bits()
{
	int	fd;
	char	*name;
	int	tok_idx;
	t_token_list	*token_list;
	char	str[BUF_SIZE];
	int		str_idx;
	const char* tokenstr[]={"label","instruction", "register", "separator", "direct_label", "direct", "indirect"};

	name = get_name(get_source()->argc);
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC);
	tok_idx = 0;
	token_list = get_token_list();
	str_idx = 0;
	while (tok_idx != token_list->token_count)
	{
		if (token_list->tokens[tok_idx].type != separator && token_list->tokens[tok_idx].type != label )
			ft_printf("%s %s\n", tokenstr[token_list->tokens[tok_idx].type], token_list->tokens[tok_idx].content);
		if (token_list->tokens[tok_idx].type == instruction)
			handle_instruction(str, &str_idx, &tok_idx);
		else
			tok_idx++; //note
	}
	write(fd, str, str_idx);
}

int	main(int ac, char **av)
{
	init_parser();
	validate_argument(ac, av);
	parser(read_file(av[1]));
	token_check();
	label_list_check();
	things_into_bits();
	// print_tokens();

	return (0);
}

