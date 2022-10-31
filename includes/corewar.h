/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:32:42 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/31 11:05:44 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include <fcntl.h>
# include "libftprintf.h"
# include "op.h"
# include <stdint.h> //used for types in linux - remove before submitting the project

# define NOT_SET -1

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
int			parse(t_header_t *player, char **argv, uint32_t argc);

//player_handler.c
void		assign_player(t_header_t *player, unsigned char *file, int8_t p_num);
void		player_sort(t_header_t *player, uint8_t p_count);

//error.c
void		check_file_size(uint32_t size);
void		check_file_type(unsigned char *file);
void		check_err_malloc(void *ptr);
void		print_man_page(void);
uint32_t	check_valid_arg(unsigned char *arg);
void		check_num_within_range(uint8_t num);

//process.c
void		process_init(t_header_t *player, uint8_t p_count);

//utilities.c
int			get_4byte(unsigned char *size_byte);
void		initialize(t_header_t *player);

//corewar.c
void		corewar(t_header_t *player, uint8_t p_count);

//test functions
void		print_mem(int size, unsigned char *mem);
void		print_process(t_process *process);
void		print_all_process(t_process *head);

#endif
