/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:13:37 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/11 18:13:19 by qnguyen          ###   ########.fr       */
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

void	assign_player(t_header_t *player, unsigned char *file, int8_t id, uint16_t ret)
{
	static uint8_t	p_num;
	uint16_t		idx;

	player[p_num].id = id;
	idx = 4;
	idx += get_data(player[p_num].prog_name, &file[idx], PROG_NAME_LENGTH);
	idx += get_size(&player[p_num].prog_size, &file[idx]);
	idx += get_data(player[p_num].comment, &file[idx], COMMENT_LENGTH);
	check_matching_champ_size(player[p_num].prog_size, ret - idx);
	player[p_num].code = ft_memalloc(ret - idx);
	get_data(player[p_num].code, &file[idx], player[p_num].prog_size);
	p_num++;
}
