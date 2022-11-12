/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_four.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:18:53 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/13 01:31:07 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"
void	verbose_live(t_process *process, t_arg *arg, t_game_param *game)
{
	ft_printf(" %d\n", get_arg_value(process, &arg[0]));
}

void	verbose_l_ld(t_process *process, t_arg *arg, t_game_param *game)
{
	ft_printf(" %d r%d\n", arg[0].value, arg[1].value);
}

void	verbose_st(t_process *process, t_arg *arg, t_game_param *game)
{
	ft_printf(" r%d %d\n", arg[0].value, (int16_t)arg[1].value);
}

void	verbose_add_sub(t_process *process, t_arg *arg, t_game_param *game)
{
	uint8_t	i;

	i = 0;
	while (i < 3)
		ft_printf(" r%d", arg[i++].value);
	ft_printf("\n");
}

void	verbose_and_or_xor(t_process *process, t_arg *arg, t_game_param *game)
{
	ft_printf(" %d", arg[0].value);
	ft_printf(" %d", arg[1].value);
	ft_printf(" r%d\n", arg[2].value);
}

void	verbose_zjmp(t_process *process, t_arg *arg, t_game_param *game)
{
	ft_printf(" %d", (int16_t)arg[0].value);
	if (process->carry)
		ft_printf(" OK\n");
	else
		ft_printf(" FAILED\n");
}

void	verbose_l_ldi(t_process *process, t_arg *arg, t_game_param *game)
{
	ft_printf(" %d", arg[0].value);
	ft_printf(" %d", arg[1].value);
	ft_printf(" r%d\n", arg[2].value);
	if (process->cmd == 9)
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n", arg[0].value, arg[1].value, arg[0].value + arg[1].value, process->pc + (int32_t)(arg[0].value + arg[1].value) % IDX_MOD);
	else
		ft_printf("       | -> load from %d + %d = %d (with pc %d)\n", arg[0].value, arg[1].value, arg[0].value + arg[1].value, process->pc + arg[0].value + arg[1].value);
}

void	verbose_sti(t_process *process, t_arg *arg, t_game_param *game)
{
	ft_printf(" r%d", arg[0].value);
	ft_printf(" %d", arg[1].value);
	ft_printf(" %d\n", arg[2].value);
	ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n", arg[1].value, arg[2].value, arg[1].value + arg[2].value, process->pc + (int32_t)(arg[1].value + arg[2].value) % IDX_MOD);
}

void	verbose_l_foork(t_process *process, t_arg *arg, t_game_param *game)
{
	uint32_t	position;

	if (process->cmd == 11)
		position = process->pc + (int16_t)arg[0].value % IDX_MOD;
	else
		position = process->pc + (int16_t)arg[0].value;
	ft_printf(" %d (%d)\n", (int16_t)arg[0].value, position);
}

void	verbose_aff(t_process *process, t_arg *arg, t_game_param *game)
{

}
