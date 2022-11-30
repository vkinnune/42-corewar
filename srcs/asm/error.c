/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:09:33 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/30 19:02:54 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void	check_open_error(int fd)
{
	if (fd == -1)
	{
		ft_printf("Unable to open the file\n");
		exit(0);
	}
}

void	label_list_error()
{
	int			i;
	t_label		*temp;
	t_label		**labels;

	i = 0;
	labels = get_labels();
	while (i < HASH_SIZE)
	{
		if (labels[i])
		{
			if (labels[i]->is_init == false)
				ft_out("ERROR ON LABELS");
			temp = labels[i]->next;
			while (temp)
			{
				if (temp->is_init == false)
					ft_out("ERROR ON LABELS");
				temp = temp->next;
			}
		}
		i++;
	}
}
