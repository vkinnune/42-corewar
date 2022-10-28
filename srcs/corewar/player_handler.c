/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:13:37 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/28 17:22:00 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static int	get_size(unsigned int *prog_size, unsigned char *size_byte)
{
	*prog_size = get_4byte(size_byte);
	return (4);
}

static int	get_data(unsigned char *player_data, unsigned char *data, int size)
{
	ft_memcpy(player_data, data, size);
	return (size + 4);
}

static void	introduce_le_champ(t_header_t *player, int p_num)
{
	ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\")!\n",
		p_num + 1, player[p_num].prog_size,
		player[p_num].prog_name, player[p_num].comment);
}

int	assign_player(t_header_t *player, unsigned char *file)
{
	static int		p_num;
	unsigned char	*idx;

	idx = file + check_file_type(file);
	idx += get_data(player[p_num].prog_name, idx, PROG_NAME_LENGTH);
	idx += get_size(&player[p_num].prog_size, idx);
	check_file_size(player[p_num].prog_size);
	idx += get_data(player[p_num].comment, idx, COMMENT_LENGTH);
	player[p_num].code = ft_memalloc(player[p_num].prog_size);
	get_data(player[p_num].code, idx, player[p_num].prog_size);
	introduce_le_champ(player, p_num);
	p_num++;
	return (p_num);
}
