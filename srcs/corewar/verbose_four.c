/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_four.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:18:53 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/29 15:36:50 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	verbose_live(t_process *process, t_arg *arg)
{
	ft_printf(" %d\n", get_arg_value(process, &arg[0]));
}

void	verbose_l_ld(t_process *process, t_arg *arg)
{
	ft_printf(" %d r%d\n", arg[0].value, arg[1].value);
}

void	verbose_st(t_process *process, t_arg *arg)
{
	ft_printf(" r%d %d\n", arg[0].value, (int16_t)arg[1].value);
}

void	verbose_add_sub(t_process *process, t_arg *arg)
{
	ft_printf(" r%d r%d r%d\n", arg[0].value, arg[1].value, arg[2].value);
}

void	verbose_and_or_xor(t_process *process, t_arg *arg)
{
	ft_printf(" %d %d r%d\n", arg[0].value, arg[1].value, arg[2].value);
}

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
		arg[1].value, arg[2].value,	pos, process->pc + (pos) % IDX_MOD);
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
