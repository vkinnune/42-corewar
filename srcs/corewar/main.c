/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:10:51 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/11 18:59:28 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

unsigned char	g_arena[MEM_SIZE];
uint8_t			g_p_count;
t_flag			g_flags;

int	main(int argc, char **argv)
{
	t_header_t	player[MAX_PLAYERS];

	if (argc < 2)
		print_man_page();
	flag_init();
	initialize_players(player);
	parse(player, argv, argc);
	corewar(player);
	return (0);
}
