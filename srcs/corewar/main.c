/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:10:51 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/28 12:00:03 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	print_man_page(void)
{
	ft_printf("man page goes here\n");
	exit(0);
}

int	main(int argc, char **argv)
{
	int			fd;
	int			ret;
	char		*str;
	int			i;
	t_header_t	player_header[4];
	t_player	player[4];

	if (argc < 2)
		print_man_page();
	i = 1;
	while (i < argc)
	{
		fd = open(argv[i], O_RDONLY);
		str = ft_memalloc(sizeof(char) * MEM_SIZE * 2);
		ret = read(fd, str, MEM_SIZE);
		if (ft_strstr(argv[i], "."))
			assign_player(player_header, player, str);
		close(fd);
		i++;
	}
	return (0);
}
