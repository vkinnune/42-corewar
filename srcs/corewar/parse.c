/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:09:11 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/30 23:15:32 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	flag_handler(char **arg, uint8_t i
			, uint8_t *p_num, uint64_t *dump_nbr)
{
	//what if i + 1 doesnt exist
	if (!ft_strcmp(arg[i], "-n"))
		*p_num = ft_atoi(arg[i + 1]);
	else if (!ft_strcmp(arg[i], "-dump"))
		*dump_nbr = ft_atoi(arg[i + 1]);
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

int	parse(t_header_t *player, char **argv, uint32_t argc)
{
	uint8_t			p_count;
	uint8_t			i;
	int8_t			p_num;
	uint64_t		dump_nbr;
	unsigned char	str[MEM_SIZE];

	i = 1;
	p_count = 0;
	p_num = -1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
			flag_handler(argv, i++, &p_num, &dump_nbr);
		else
		{
			get_file_content(str, argv[i]);
			assign_player(player, str, p_num);
			p_num = -1;
			p_count++;
		}
		i++;
	}
	//sort players into their correct indices
	return (p_count);
}
