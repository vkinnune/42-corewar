/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:10:51 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/31 12:09:55 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

unsigned char	g_arena[MEM_SIZE];

int	main(int argc, char **argv)
{
	uint8_t			p_count;
	t_header_t		player[MAX_PLAYERS];

	if (argc < 2)
		print_man_page();
	initialize(player);
	p_count = parse(player, argv, argc);
	corewar(player, p_count);
	return (0);
}
