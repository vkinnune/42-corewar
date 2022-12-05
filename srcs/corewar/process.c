/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:22:00 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/01 20:20:52 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	read_instruction(t_process *process)
{
	uint8_t	instruction_code;

	if (process->cmd == -1)
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
	int		i;

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
}

void	processor(t_game_param *game, t_table *tab, t_header_t *player)
{
	t_process	*process;

	process = game->head;
	while (process)
	{
		read_instruction(process);
		if (process->wait_cycle == 0)
		{
			execute_le_code(game, process, tab, player);
			if (g_flags.verbose & 16)
				print_sixteen(process);
			process->pc = get_position(process->pc + process->bytes_to_next);
			process->cmd = -1;
			process->bytes_to_next = 1;
		}
		process = process->next;
	}
}
