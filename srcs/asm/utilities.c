/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:22:35 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/27 17:49:59 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void	cor_init(t_file *cor, uint8_t **name, int *fd)
{
	cor->str = (unsigned char *)ft_memalloc(COR_FILE_SIZE);
	cor->idx = 0;
	*name = get_name(get_source()->argc);
	*fd = open(*name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	check_open_error(*fd);
}
