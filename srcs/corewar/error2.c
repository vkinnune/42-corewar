/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:16:49 by jrummuka          #+#    #+#             */
/*   Updated: 2022/12/05 22:58:23 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	check_existing_id(int8_t id)
{
	ft_printf("%d\n", id);
	if (id != NOT_SET)
		ft_out("Pwayers can has no same id (っ´ω｀c)");
}

void	check_missing_id(int8_t id)
{
	if (id == NOT_SET)
		ft_out("There's empty space in my heart Senpai (⁄ ⁄•⁄ω⁄•⁄ ⁄)");
}
