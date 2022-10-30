/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:29:55 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/28 21:52:25 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_parser	*get_parser()
{
	static	t_parser	parse;

	return (&parse);
}

t_token_list	*get_token_list()
{
	t_parser	*parse;

	parse = get_parser();
	return (&parse->token_list);
}

void	init_parser()
{
	t_parser	*parse;

	parse = get_parser();
	ft_bzero(parse, sizeof(t_parser));
}

int	label_check(char *line, int len)
{
	int	i;

	i = 0;
	while (i != len)
	{
		if (line[i] == ':')
			return (1);
		i++;
	}
	return (0);
}

void	save_token(char *line, int len, t_token_type token_type)
{
	t_token_list	*token_list;

	token_list = get_token_list();
	token_list->tokens[token_list->token_count].type = token_type;
	token_list->token_count++;
}

int	check_valid(char *line, int len)
{
	t_token_type	token_type;

	if (label_check(line, len))
		token_type = label;
	/*
	else if (instruction_check())
		;
	else if (register_check())
		;
	else if (separator_check())
		;
	else if (direct_label_check())
		;
	else if (direct_check())
		;
		*/
	else
		return (0);
	save_token(line, len, token_type);
	return (1);
}

void	parser(const char *input)
{
	char	*forward_p;
	char	*stay_p;

	forward_p = (char *)input;
	stay_p = (char *)input;
	while (*forward_p)
	{
		if (check_valid(stay_p, forward_p - stay_p))
			stay_p = forward_p + 1;
		forward_p++;
	}
}

char *read_file(char *file_name)
{
	int		fd;
	char	buf[BUF_SIZE];
	int		ret;
	int		read_size;
	char	*str;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		ft_out(CANNOT_OPEN_FILE);
	ret = 1;
	str = 0;
	read_size = 0;
	while (ret)
	{
		ret = read(fd, buf, BUF_SIZE);
		read_size += ret;
		str = realloc(str, read_size);
		ft_memcpy(str, buf, ret);
	}
	return (str);
}

int	main(int ac, char **av)
{
	init_parser();
	validate_argument(ac, av);
	parser(read_file(av[1]));
	return (0);
}

