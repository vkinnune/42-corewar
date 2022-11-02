/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:29:55 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/31 15:06:38 by vkinnune         ###   ########.fr       */
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

t_source	*get_source()
{
	t_parser	*parse;

	parse = get_parser();
	return (&parse->source);
}

void	init_parser()
{
	t_parser	*parse;

	parse = get_parser();
	ft_bzero(parse, sizeof(t_parser));
}

int	label_check(char **p)
{
	int	i;

	i = 0;
	while (1)
	{
		if ((*p)[i] == ':')
		{
			*p = &(*p)[i + 1];
			return (1);
		}
		else if ((*p)[i] == '\n' || (*p)[i] == '\0')
			return (0);
		i++;
	}
}

int	instruction_check(char **p)
{
	int	i;

	i = 0;
	while ()
	{

	}
	return (0);
}

void	save_token(char **p, t_token_type token_type)
{
	t_token_list	*token_list;

	token_list = get_token_list();
	token_list->tokens[token_list->token_count].type = token_type;
	token_list->token_count++;
}

int	check_valid(char **p)
{
	t_token_type	token_type;

	if (label_check(p))
		token_type = label;
	else if (instruction_check(p))
		token_type = instruction;
	/*else if (register_check())
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
	save_token(p, token_type);
	return (1);
}

int	move_forward(char **p)
{
	t_source	*source;

	source = get_source();
	if (**p == '\n')
	{
		source->row++;
		source->col = 0;
	}
	else if (**p == '\0')
		return (0);
	(*p)++;
	source->col++;
	return (1);
}

void	handle_asm(char *p)
{
	while (move_forward(&p))
	{
		if (*p == ' ' || *p == '\t' || *p == '\n')
			continue ;
		else if (!check_valid(&p))
		{
			printf("Error in col: %d row: %d", get_source()->col, get_source()->col);
			exit(EXIT_FAILURE);
		}
	}
}

char	*save_header_string(char *p, t_header_type type)
{
	char	*saved_string;
	char	*stay_p;

	stay_p = 0;
	while (1)
	{
		if (*p == '\"')
		{
			if (stay_p)
			{
				if (type == name && (p - stay_p) < NAME_SIZE)
					ft_memcpy(get_source()->name, &stay_p[1], (p - stay_p) - 1);
				else if (type == comment && (p - stay_p) < COMMENT_SIZE)
					ft_memcpy(get_source()->comment, &stay_p[1], (p - stay_p) - 1);
				else
					ft_out(HEADER_TOO_BIG);
				break ;
			}
			stay_p = p;
		}
		else if (*p != ' ' && *p != '\t' && !stay_p)
			ft_out(HEADER_ERROR);
		p++;
	}
	return (p + 1);
}

char	*handle_header(const char *input)
{
	char	*p;

	p = (char *)input;
	while (!*(get_source()->name) || !*(get_source()->comment))
	{
		if (*p == '\t' || *p == ' ' || *p == '\n')
			p++;
		else if (!ft_strncmp(".name", p, 5))
			p = save_header_string(&p[5], name);
		else if (!ft_strncmp(".comment", p, 8))
			p = save_header_string(&p[8], comment);
		else
			ft_out(HEADER_ERROR);
	}
	return (p);
}

void	parser(const char *input)
{
	char	*p;

	//handle header, handle header goes to the start of the asm
	p = handle_header(input);
	//handle asm
	handle_asm(p);
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

void	print_tokens()
{
	int	i;
	t_token_list	*token_list;

	token_list = get_token_list();
	i = 0;
	while (i != token_list->token_count)
	{
		ft_printf("%d ", token_list->tokens[i].type);
		i++;
	}
}

int	main(int ac, char **av)
{
	init_parser();
	validate_argument(ac, av);
	parser(read_file(av[1]));
	print_tokens();
	return (0);
}

