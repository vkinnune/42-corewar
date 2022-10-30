/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:09:11 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/30 20:50:56 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int	parse(t_header_t *player, char *arg)
{
	uint8_t			p_count;
	uint16_t		fd;
	uint32_t		ret;
	unsigned char	str[MEM_SIZE];

	// if (arg == option flags)
	// {
		//do_the_thing();
		//return (0);
	// }
	fd = open(arg, O_RDONLY);
	ret = read(fd, str, MEM_SIZE);
	check_file_type(str);
	close(fd);
	return (assign_player(player, str));
}
