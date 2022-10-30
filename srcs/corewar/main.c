/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:10:51 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/30 20:56:47 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

unsigned char	g_arena[MEM_SIZE];

void	print_man_page(void)
{
	ft_printf("man page goes here\n");
	exit(0);
}

void	arena_init(t_header_t *player, int p_count)
{
	uint8_t		i;
	uint16_t	p_start;

	ft_bzero((void *)g_arena, MEM_SIZE);
	i = 0;
	p_start = 0;
	while (i < p_count)
	{
		ft_memcpy(g_arena + p_start, player[i].code, player[i].prog_size);
		p_start += MEM_SIZE / p_count;
		i++;
	}
}

int	main(int argc, char **argv)
{
	uint8_t			i;
	uint8_t			p_count;
	t_header_t		player[4];

	if (argc < 2)
		print_man_page();
	i = 1;
	while (i < argc)
	{
		p_count = parse(player, argv[i]);
		i++;
	}
	arena_init(player, p_count);
	process_init(player, p_count);
	return (0);
}

//	print_mem(player[0].prog_size, player[0].code); // print player data
//	print_mem(MEM_SIZE, arena); // print arena