/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:32:42 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/28 13:06:22 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <fcntl.h>
# include "libftprintf.h"
# include "op.h"

typedef struct s_player
{
	char	*code;
}				t_player;

void	assign_player(t_header_t *header, t_player *player, unsigned char *file);

//error.c
void	check_file_size(int size);
int		check_file_type(unsigned char *file);

//utilities.c
int		get_4byte(unsigned char *size_byte);

//test functions
void	print_code(int prog_size, t_player *player);

#endif