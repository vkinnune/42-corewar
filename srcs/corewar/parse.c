/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:09:11 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/28 16:51:15 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int	parse(t_header_t *player, char *file_name)
{
	int				fd;
	int				ret;
	int				p_count;
	unsigned char	str[MEM_SIZE];

	//check if flag
	fd = open(file_name, O_RDONLY);
	ret = read(fd, str, MEM_SIZE);
	close(fd);
	if (ft_strstr(file_name, "."))
		return (assign_player(player, str));
	return (0);
}
