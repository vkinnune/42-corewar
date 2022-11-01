/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:10:51 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/01 16:53:46 by jrummuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

unsigned char	g_arena[MEM_SIZE];
uint8_t			g_p_count;
uint64_t		g_dump_nbr;

int	main(int argc, char **argv)
{
	t_header_t	player[MAX_PLAYERS];
	t_flag		flags;

	if (argc < 2)
		print_man_page();
	initialize(player);
	parse(player, argv, argc, &flags);
	corewar(player, &flags);
	return (0);
}
