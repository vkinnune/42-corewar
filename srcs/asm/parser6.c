/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:11:52 by vkinnune          #+#    #+#             */
/*   Updated: 2022/12/05 23:09:05 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

char	*read_file(char *file_name)
{
	int		fd;
	char	buf[BUF_SIZE];
	int		ret;
	int		read_size;
	char	*str;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		ft_out("Error: File does not exist");
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

char	*handle_header(const char *input)
{
	char	*p;
	bool	is_newline;

	p = (char *)input;
	is_newline = false;
	init_name_comment();
	while ((!*(get_source()->name) && (!(get_source()->save_name)))
		|| (!*(get_source()->comment) && (!(get_source()->save_comment))))
		p = check_string_comment_name(&is_newline, p);
	if (is_newline == false)
		ft_out("Error: No newline in comment and name");
	return (p);
}

int	direct_label_check(char **p)
{
	int	i;

	i = 2;
	if ((*p)[0] == '%' && (*p)[1] == ':')
	{
		while (ft_isprint((*p)[i]) && (*p)[i] != ','
			&& (*p)[i] != ' ' && (*p)[i] != '\t' && (*p)[i] != '\n')
			i++;
		if (i > 2)
		{
			get_source()->col += (i - 1);
			*p = &(*p)[i - 1];
			return (1);
		}
	}
	return (0);
}
