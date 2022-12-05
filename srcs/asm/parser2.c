/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:29:55 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/05 16:26:24 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void	handle_stay_p(char *stay_p, char *p, t_header_type type)
{
	if (type == name && (p - stay_p) < PROG_NAME_LENGTH)
		ft_memcpy(get_source()->name, &stay_p[1], (p - stay_p) - 1);
	else if (type == comment && (p - stay_p) < COMMENT_LENGTH)
		ft_memcpy(get_source()->comment, &stay_p[1],
			(p - stay_p) - 1);
	else
		ft_out(HEADER_TOO_BIG);
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
				handle_stay_p(stay_p, p, type);
				break ;
			}
			stay_p = p;
		}
		else if ((*p != ' ' && *p != '\t' && !stay_p) || (*p == '\0'))
			ft_out(HEADER_ERROR);
		p++;
	}
	return (p + 1);
}

void	one_more_function(void)
{
	get_source()->row = 2;
	get_source()->col = 0;
	ft_bzero(get_source()->name, PROG_NAME_LENGTH);
	ft_bzero(get_source()->comment, COMMENT_LENGTH);
}

char	*handle_header(const char *input)
{
	char	*p;
	bool	is_newline;

	p = (char *)input;
	is_newline = false;
	one_more_function();
	while (!*(get_source()->name) || !*(get_source()->comment))
	{
		if (*p == '\t' || *p == ' ' || *p == '\n')
		{
			if (*p == '\n')
				is_newline = true;
			p++;
		}
		else if (!ft_strncmp(NAME_CMD_STRING, p, 5))
			p = save_header_string(&p[5], name);
		else if (!ft_strncmp(COMMENT_CMD_STRING, p, 8))
			p = save_header_string(&p[8], comment);
		else
			ft_out(HEADER_ERROR);
	}
	if (is_newline == false)
		ft_out("Error: No newline in comment and name");
	return (p);
}

char	*read_file(char *file_name)
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
		str = realloc(str, read_size + 1);
		ft_memcpy(str, buf, ret);
	}
	str[read_size] = 0;
	return (str);
}
