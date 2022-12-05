/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:11:52 by vkinnune          #+#    #+#             */
/*   Updated: 2022/12/05 18:12:06 by vkinnune         ###   ########.fr       */
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
