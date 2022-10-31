/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:05:02 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/31 11:05:22 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	copy_with_id(t_header_t *player, t_header_t *temp, uint8_t p_count)
{
	uint8_t	i;

	i = 0;
	while (i < p_count)
	{
		if (player[i].id != NOT_SET)
			ft_memcpy((void *)&temp[player[i].id - 1], (void *)&player[i],
				sizeof(player[i]));
		i++;
	}
}

static void	copy_no_id(t_header_t *player, t_header_t *temp, uint8_t p_count)
{
	uint8_t	i;
	uint8_t	j;

	j = 0;
	i = 0;
	while (i < p_count)
	{
		if (player[i].id == NOT_SET)
		{
			while (temp[j].id != NOT_SET && j < p_count)
				j++;
			ft_memcpy((void *)&temp[j], (void *)&player[i], sizeof(player[i]));
			temp[j].id = j + 1;
		}
		i++;
	}
}

void	player_sort(t_header_t *player, uint8_t p_count)
{
	t_header_t	temp[MAX_PLAYERS];

	initialize(temp);
	copy_with_id(player, temp, p_count);
	copy_no_id(player, temp, p_count);
	ft_memcpy((void *)player, (void *)temp, sizeof(temp));
}
