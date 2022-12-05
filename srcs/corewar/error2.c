/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:16:49 by jrummuka          #+#    #+#             */
/*   Updated: 2022/12/05 17:43:20 by jrummuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	check_existing_id(int8_t id)
{
	ft_printf("%d\n", id);
	if (id != NOT_SET)
	{
		ft_printf("Pwayers can has no same id (っ´ω｀c)\n");
		print_and_exit(0);
	}
}

void	check_missing_id(int8_t id)
{
	if (id == NOT_SET)
	{
		ft_printf("There's empty space in my heart Senpai (⁄ ⁄•⁄ω⁄•⁄ ⁄)\n");
		print_and_exit(0);
	}
}
