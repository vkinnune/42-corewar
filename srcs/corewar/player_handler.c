/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:13:37 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/02 18:38:52 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static int	get_size(unsigned int *prog_size, unsigned char *size_byte)
{
	*prog_size = get_n_byte(4, size_byte);
	check_file_size(*prog_size);
	return (4);
}

static int	get_data(unsigned char *player_data, unsigned char *data, int size)
{
	ft_memcpy(player_data, data, size);
	return (size + 4);
}

void	assign_player(t_header_t *player, unsigned char *file, int8_t id)
{
	static uint8_t	p_num;
	unsigned char	*idx;

	player[p_num].id = id;
	idx = file + 4;
	idx += get_data(player[p_num].prog_name, idx, PROG_NAME_LENGTH);
	idx += get_size(&player[p_num].prog_size, idx);
	idx += get_data(player[p_num].comment, idx, COMMENT_LENGTH);
	player[p_num].code = ft_memalloc(player[p_num].prog_size);
	get_data(player[p_num].code, idx, player[p_num].prog_size);
	p_num++;
}
