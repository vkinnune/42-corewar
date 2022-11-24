/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:10:51 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/22 01:47:51 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"
unsigned char	g_arena[MEM_SIZE];
uint8_t			g_p_count;
t_flag			g_flags;

void	print_man_page(void)
{
	ft_printf("SYNOPSIS\n"
	"\t./corewar [-dump N] [-d N] [-v N] [-n] <champ.cor>\n\n"
	"OPTIONS\n"
	"\t-dump\n"
	"\t\tStop at Nth cycle and dump the memory into 32 bytes per line\n"
	"\t-d\n\t\tSimilar to -dump but prints 64 bytes per line instead\n"
	"\t-v\n\t\tVerbose printing:\n"
	"\t\t\t 1: Prints when a player is live\n"
	"\t\t\t 2: Prints cycle\n"
	"\t\t\t 4: Prints instructions (Params are NOT litteral ...)\n"
	"\t\t\t 8: Prints deaths\n"
	"\t\t\t16: hihi (*^▽^*)\n"
	"\t-n\n"
	"\t\tAssign the player's number manually\n");
	exit(0);
}

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
