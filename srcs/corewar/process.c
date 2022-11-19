/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:22:00 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/19 06:05:16 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	read_instruction(t_process *process)
{
	uint8_t	instruction_code;

	if (process->cmd == -1) //no cmd
	{
		instruction_code = g_arena[process->pc];
		if (instruction_code < 0x01 || instruction_code > 0x10)
		{
			process->pc = get_position(process->pc + 1);
			process->wait_cycle = -1;
			return ;
		}
		process->cmd = instruction_code - 1;
		process->wait_cycle = op_tab[process->cmd].wait_cycle;
	}
	process->wait_cycle--;
}

void	update_live_player(t_game_param *game, t_process *process
					, t_arg *arg, t_header_t *player)
{
	uint16_t	i;

	i = 0;
	while (i < g_p_count)
	{
		// ft_printf("%u -- %u: %s\n", arg[i].value  -player[i].id, player[i].prog_name);
		if (arg[0].value == -player[i].id)
		{
			game->last_alive = player[i].id;
			if (g_flags.verbose & 1)
				ft_printf("Player %d (%s) is said to be alive\n", player[i].id, player[i].prog_name);
		}
		i++;
	}
}

static void	execute_le_code(t_game_param *game, t_process *process, t_table *tab, t_header_t *player)
{
	t_arg	arg[3];

	ft_bzero((void *)arg, sizeof(arg));
	if (check_matching_arg(process, arg) != OKEI)
		return ;
	if (op_tab[process->cmd].arg_byte == 0)
		get_arg_without_arg_byte(process, &arg[0]);
	tab->instruct_table[process->cmd](process, arg, game);
	if ((g_flags.verbose & 4) && process->cmd != 15)
	{
		ft_printf("P %4d | %s", process->id + 1, op_tab[process->cmd].name);
		tab->verbose_table[process->cmd](process, arg);
	}
	if (process->cmd == 0)
		update_live_player(game, process, arg, player);
/* 	if (process->id + 1 == 3)
	{
		ft_printf("\tpc pos: %d\n", process->pc);
		ft_printf("\tcmd: %s\n", op_tab[process->cmd].name);
		// ft_printf("arg :%d\n", get_arg_value(process, &arg[0]));
		ft_printf("\tcarry %d\n", process->carry);
	} */
}

void	processor(t_game_param *game, t_table *tab, t_header_t *player)
{
	t_process	*process;

	process = game->head;
	while (process)
	{
		read_instruction(process);
/* 		if (game->current_cycle == 13856 && process->id + 1 == 1026)
		{
			ft_printf("\tcycle: %d\n", game->current_cycle);
			ft_printf("\tpc: %d: %02x\n", process->pc, g_arena[process->pc]);
			ft_printf("\twait: %d\n", process->wait_cycle);
		} */
		if (process->wait_cycle == 0)
		{
			execute_le_code(game, process, tab, player);
			process->pc = get_position(process->pc + process->bytes_to_next);
			// ft_printf("P%d move to @%u ╰(⸝⸝⸝´꒳`⸝⸝⸝)╯ \n", process->id + 1, process->pc);
			process->cmd = -1;
			process->bytes_to_next = 1;
		}
		process = process->next;
	}
}
