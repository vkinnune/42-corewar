/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:41:52 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/26 18:30:11 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	colored_arena(t_header_t *player, int i, int p_area)
{
	if (i == p_area * 0)
		ft_printf("$g");
	else if (i == p_area * 1 )
		ft_printf("$b");
	else if (i == p_area * 2)
		ft_printf("$r");
	else if (i == p_area * 3 && g_p_count > 3)
		ft_printf("$b");
	else if (i == p_area * 0 + player[0].prog_size
		|| i == p_area * 1 + player[1].prog_size
		|| i == p_area * 2 + player[2].prog_size
		|| i == p_area * 3 + player[3].prog_size)
		ft_printf("$d");
}

void	print_arena(t_header_t *player)
{
	int	i;
	int	p_area;

	p_area = (MEM_SIZE / g_p_count);
	i = 0;
	while (i < MEM_SIZE)
	{
		// colored_arena(player, i, p_area);
		if (i % g_flags.byte == 0)
		{
			if (i != 0)
				ft_printf("\n%#06x :", i);
			else
				ft_printf("0x0000 :"); // quick fix until i fix my printf
		}
		ft_printf(" %02x", g_arena[i++]);
	}
	ft_printf("\n");
}
