/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:13:37 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/28 11:52:00 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static int	validate_file_type(char *file)
{
	if (file[0] == 0
		&& file[1] == 0xffffffea
		&& file[2] == 0xffffff83
		&& file[3] == 0xfffffff3)
		return (4);
	ft_printf("What are you putting into me senpai >///<\n");
	//free_everything();
	exit (0);
}

static int	get_size(t_header_t *header, char *size_byte)
{
	header->prog_size = size_byte[0] + size_byte[1]
		+ size_byte[2] + size_byte[3];
	return (4);
}

static int	get_data(char *player_data, char *data, int size)
{
	ft_memcpy(player_data, data, size);
	return (size + 4);
}

void	introduce_le_champ(t_header_t *header, t_player *player, int p_num)
{
	ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\")!\n",
		p_num + 1, header[p_num].prog_size,
		header[p_num].prog_name, header[p_num].comment);
}

void	assign_player(t_header_t *header, t_player *player, char *file)
{
	static int	p_num;
	char		*idx;

	idx = file + validate_file_type(file);
	idx += get_data(header[p_num].prog_name, idx, PROG_NAME_LENGTH);
	idx += get_size(&header[p_num], idx);
	idx += get_data(header[p_num].comment, idx, COMMENT_LENGTH);
	player[p_num].code = ft_memalloc(header[p_num].prog_size);
	get_data(player[p_num].code, idx, header[p_num].prog_size);
	introduce_le_champ(header, player, p_num);
	//print_code(header[p_num].prog_size, &player[p_num]);
	p_num++;
}

//test functions

void	print_code(int prog_size, t_player *player)
{
	int	i;

	i = 0;
	while (i < prog_size)
	{
		ft_printf("%02x ", player->code[i++]);
	}
	ft_printf("\n");
}
