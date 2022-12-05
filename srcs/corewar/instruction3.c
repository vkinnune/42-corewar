/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:19:32 by jrummuka          #+#    #+#             */
/*   Updated: 2022/12/05 17:52:18 by jrummuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	l_foork(t_process *process, t_arg *arg, t_game_param *game)
{
	uint8_t		i;
	t_process	*new;
	int32_t		position;

	if (process->cmd == 11)
		position = process->pc + (int16_t)arg[0].value % IDX_MOD;
	else
		position = process->pc + (int16_t)arg[0].value;
	position = get_position(position);
	new = new_process(game->head, position, -process->reg[r1]);
	i = 0;
	while (++i <= r16)
		new->reg[i] = process->reg[i];
	new->carry = process->carry;
	new->last_live_cycle = process->last_live_cycle;
	new->cmd = -1;
	process->bytes_to_next += DIR_SIZE / 2;
	game->head = new;
}

void	aff(t_process *process, t_arg *arg, t_game_param *game)
{
	char	a;

	if (g_flags.aff == SET)
	{
		a = (char)get_arg_value(process, &arg[0]);
		ft_printf("Aff: %c\n", a);
	}
	(void)game;
}
