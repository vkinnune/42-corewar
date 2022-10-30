/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:32:42 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/30 21:11:13 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <fcntl.h>
# include "libftprintf.h"
# include "op.h"
#include <stdint.h> //used for types in linux - dont fix this norm - remove before submitting the project

unsigned char	g_arena[MEM_SIZE];

typedef struct s_process t_process;

struct s_process
{
	uint8_t		instruction :5;
	uint8_t		carry :1; //one-bit var
	uint16_t	prog_counter; //current position
	uint16_t	bytes_to_next_instr;
	uint16_t	wait_cycle; //amount of waiting until executing $(instruction)
	uint32_t	process_id;
	uint32_t	last_live_cycle;
	uint32_t	reg[REG_NUMBER]; //??
	t_process	*next;
};

//parse.c
int		parse(t_header_t *player, char *arg);

//player_handler.c
int		assign_player(t_header_t *player, unsigned char *file);

//error.c
void	check_open(int fd);
void	check_file_size(int size);
void	check_file_type(unsigned char *file);
void	check_err_malloc(void *ptr);

//process.c
void	process_init(t_header_t *player, int p_count);

//utilities.c
int		get_4byte(unsigned char *size_byte);

//test functions
void	print_mem(int size, unsigned char *mem);
void	print_process(t_process *process);
void	print_all_process(t_process *head);

#endif