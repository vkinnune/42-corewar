/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:10:51 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/28 19:45:47 by jrummuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	print_man_page(void)
{
	ft_printf("man page goes here\n");
	exit(0);
}

void	arena_init(unsigned char *arena, t_header_t *player, int p_count)
{
	int	i;
	int	p_start;

	ft_bzero((void *)arena, MEM_SIZE);
	i = 0;
	p_start = 0;
	while (i < p_count)
	{
		ft_memcpy(arena + p_start, player[i].code, player[i].prog_size);
		p_start += MEM_SIZE / p_count;
		i++;
	}
}

int	main(int argc, char **argv)
{
	int				i;
	int				p_count;
	t_header_t		player[4];
	unsigned char	arena[MEM_SIZE];

	if (argc < 2)
		print_man_page();
	i = 1;
	while (i < argc)
	{
		p_count = parse(player, argv[i]);
		i++;
	}
//	print_mem(player[0].prog_size, player[0].code);
	arena_init(arena, player, p_count);
//	print_mem(MEM_SIZE, arena);
	return (0);
}
