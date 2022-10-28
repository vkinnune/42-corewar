/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:32:42 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/28 17:16:44 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <fcntl.h>
# include "libftprintf.h"
# include "op.h"

typedef struct s_process t_process;

struct s_process
{
	unsigned char	instruction;
	unsigned char	carry :1; //one-bit var
	unsigned int	process_id;
	unsigned int	prog_counter; //current position
	unsigned int	last_live_cycle;
	unsigned int	bytes_to_next_instr;
	unsigned int	wait_cycle; //amount of waiting until executing $(instruction)
	unsigned int	reg[REG_NUMBER]; //??
	t_process		*next;
};

//parse.c
int		parse(t_header_t *player, char *file_name);

//player_handler.c
int		assign_player(t_header_t *player, unsigned char *file);

//error.c
void	check_file_size(int size);
int		check_file_type(unsigned char *file);

//utilities.c
int		get_4byte(unsigned char *size_byte);

//test functions
void	print_mem(int size, unsigned char *mem);

#endif