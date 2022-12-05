/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:18:53 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/05 17:55:30 by jrummuka         ###   ########.fr       */
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
	(void)process;
}

void	verbose_st(t_process *process, t_arg *arg)
{
	ft_printf(" r%d %d\n", arg[0].value, (int16_t)arg[1].value);
	(void)process;
}

void	verbose_add_sub(t_process *process, t_arg *arg)
{
	ft_printf(" r%d r%d r%d\n", arg[0].value, arg[1].value, arg[2].value);
	(void)process;
}

void	verbose_and_or_xor(t_process *process, t_arg *arg)
{
	ft_printf(" %d %d r%d\n", arg[0].value, arg[1].value, arg[2].value);
	(void)process;
}
