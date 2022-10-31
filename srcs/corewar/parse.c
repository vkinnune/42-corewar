/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:09:11 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/31 10:55:50 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	flag_handler(char **arg, uint8_t i
			, uint8_t *p_num, uint64_t *dump_nbr)
{
	if (!ft_strcmp(arg[i], "-n"))
	{
		*p_num = check_valid_arg(arg[i + 1]);
		check_num_within_range(*p_num);
	}
	else if (!ft_strcmp(arg[i], "-dump"))
	{
		*dump_nbr = check_valid_arg(arg[i + 1]);
		//check if number < 0 (?)
	}
	else
		print_man_page();
}

static void	get_file_content(unsigned char *str, char *file)
{
	uint16_t	fd;

	fd = open(file, O_RDONLY);
	read(fd, str, MEM_SIZE);
	close(fd);
	check_file_type(str);
}

void	introduce_le_champ(t_header_t *player, uint8_t p_count)
{
	uint8_t	i;

	i = 0;
	while (i < p_count)
	{
		ft_printf("* Player %d @%d, weighing %d bytes, \"%s\" (\"%s\")!\n",
			player[i].id, i, player[i].prog_size,
			player[i].prog_name, player[i].comment);
		// print_mem(player[i].prog_size, player[i].code);
		i++;
	}
}

int	parse(t_header_t *player, char **argv, uint32_t argc)
{
	uint8_t			p_count; //might move this to global
	uint8_t			i;
	int8_t			id;
	uint64_t		dump_nbr; //and this too
	unsigned char	str[MEM_SIZE];

	p_count = 0;
	id = NOT_SET;
	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
			flag_handler(argv, i++, &id, &dump_nbr);
		else
		{
			get_file_content(str, argv[i]);
			assign_player(player, str, id);
			id = NOT_SET;
			p_count++;
		}
		i++;
	}
	check_num_within_range(p_count);
	player_sort(player, p_count);
	introduce_le_champ(player, p_count);
	return (p_count);
}
