/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:40:05 by jrummuka          #+#    #+#             */
/*   Updated: 2022/12/05 17:47:16 by jrummuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	verbose_zjmp(t_process *process, t_arg *arg)
{
	if (process->carry == 1)
		ft_printf(" %d OK\n", (int16_t)arg[0].value);
	else
		ft_printf(" %d FAILED\n", (int16_t)arg[0].value);
}

void	verbose_l_ldi(t_process *process, t_arg *arg)
{
	int32_t	pos;

	ft_printf(" %d %d r%d\n", arg[0].value, arg[1].value, arg[2].value);
	pos = arg[0].value + arg[1].value;
	if (process->cmd == 9)
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
			arg[0].value, arg[1].value, pos, process->pc + pos % IDX_MOD);
	else
		ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
			arg[0].value, arg[1].value, pos, process->pc + pos);
}

void	verbose_sti(t_process *process, t_arg *arg)
{
	int32_t	pos;

	ft_printf(" r%d %d %d\n", arg[0].value, arg[1].value, arg[2].value);
	pos = arg[1].value + arg[2].value;
	ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
		arg[1].value, arg[2].value, pos, process->pc + (pos) % IDX_MOD);
}

void	verbose_l_foork(t_process *process, t_arg *arg)
{
	int32_t	pos;

	if (process->cmd == 11)
		pos = process->pc + (int16_t)arg[0].value % IDX_MOD;
	else
		pos = process->pc + (int16_t)arg[0].value;
	ft_printf(" %d (%d)\n", (int16_t)arg[0].value, pos);
}
