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

uint8_t	*get_name(uint8_t*argc)
{
	int	len;
	int	name_len;
	uint8_t	*name;

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

void	handle_direct(uint8_t*str, int *str_idx, int arg_idx, int arg_location, int dir_size, uint8_t*content)
{
	int	num;

	str[arg_location] |= (uint8_t)(DIR_CODE << (2 * (3 - arg_idx)));
	ft_printf("binary %b \n", str[arg_location]);
	if (dir_size)
	{
		num = ft_atoi(&content[1]);
		str[*str_idx] += (int16_t)num;
		*str_idx += 2;
	}
	else
	{
		num = ft_atoi(&content[1]);
		str[*str_idx] += (int32_t)num;
		*str_idx += 4;
	}

}

void	handle_indirect(uint8_t*str, int *str_idx, int arg_idx, int arg_location, uint8_t*content)
{
	int	num;

	str[arg_location] |= (uint8_t)(IND_CODE << (2 * (3 - arg_idx)));
	num = ft_atoi(content);
	str[*str_idx] += (int16_t)num;
	*str_idx += 2;
}

void	handle_reg(uint8_t*str, int *str_idx, int arg_idx, int arg_location, uint8_t*content)
{
	int	num;

	str[arg_location] |= (uint8_t)(REG_CODE << (2 * (3 - arg_idx)));
	num = ft_atoi(&content[1]);
	str[*str_idx] += (int8_t)num;
	*str_idx += 1;
}

void	handle_arg_byte(uint8_t*str, int *str_idx, int op_idx, int *tok_idx)
{
	int	arg_idx;
	int	arg_location;
	t_token	*tokens;

	tokens = get_token_list()->tokens;
	str[*str_idx] = 0;
	(*tok_idx)++;
	arg_idx = 0;
	arg_location = *str_idx;
	if (op_tab[op_idx].arg_byte)
	{
		(*str_idx)++;
		while (arg_idx < op_tab[op_idx].arg_amt)
		{
			if (tokens[*tok_idx].type == direct)
				handle_direct(str, str_idx, arg_idx, arg_location, op_tab[op_idx].dir_size, tokens[*tok_idx].content);
			else if (tokens[*tok_idx].type == indirect)
				handle_indirect(str, str_idx, arg_idx, arg_location, tokens[*tok_idx].content);
			else if (tokens[*tok_idx].type == reg)
				handle_reg(str, str_idx, arg_idx, arg_location, tokens[*tok_idx].content);
			arg_idx++;
			(*tok_idx)++;
			if (tokens[*tok_idx].type == separator)
				(*tok_idx)++;
		}
		(*str_idx)++;
	}
	else
	{
		//assign dir
		if (tokens[*tok_idx].type == reg)
		{

		}
		else if (tokens[*tok_idx].type == direct)
		{

		}
		(*tok_idx)++;
	}
	ft_printf("%b \n", str[arg_location]);
}

int	handle_instruction(uint8_t*str, int *str_idx, int *tok_idx)
{
	int	op_idx;
	int amount;
	t_token	*token;

	op_idx = 0;
	token = get_token_list()->tokens;
	while(op_idx != 17)
	{
		if (!ft_strcmp(token[*tok_idx].content, op_tab[op_idx].name))
		{
			str[(*str_idx)++] = op_tab[op_idx].order_num;
			handle_arg_byte(str, str_idx, op_idx, tok_idx);
			return (0);
		}
		op_idx++;
	}
	if (op_idx == 17)
		ft_out("NOOOOOOOOOOOO");
	return (0);
}

void	things_into_bits()
{
	int	fd;
	uint8_t	*name;
	int	tok_idx;
	t_token_list	*token_list;
	uint8_t	str[BUF_SIZE];
	int		str_idx;
	const uint8_t* tokenstr[]={"label","instruction", "register", "separator", "direct_label", "direct", "indirect"};

	name = get_name(get_source()->argc);
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	printf("fd: %d\n", fd);
	tok_idx = 0;
	token_list = get_token_list();
	str_idx = 0;
	while (tok_idx != token_list->token_count)
	{
		if (token_list->tokens[tok_idx].type != separator && token_list->tokens[tok_idx].type != label)
			ft_printf("%s %s\n", tokenstr[token_list->tokens[tok_idx].type], token_list->tokens[tok_idx].content);
		if (token_list->tokens[tok_idx].type == instruction)
			handle_instruction(str, &str_idx, &tok_idx);
		else
			tok_idx++; //note
	}
	printf("fd: %d\n", fd);
	write(fd, str, str_idx);
}

int	main(int ac, char**av)
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

