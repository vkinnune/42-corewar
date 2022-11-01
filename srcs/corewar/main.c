/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:10:51 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/01 17:21:07 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

unsigned char	g_arena[MEM_SIZE];
uint8_t			g_p_count;
int64_t			g_dump_nbr;

int	main(int argc, char **argv)
{
	t_header_t	player[MAX_PLAYERS];
	t_flag		flags;

	if (argc < 2)
		print_man_page();
	g_dump_nbr = -1;
	initialize(player);
	parse(player, argv, argc, &flags);
	corewar(player, &flags);
	return (0);
}
