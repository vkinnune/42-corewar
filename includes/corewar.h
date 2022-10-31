/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:32:42 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/31 17:34:20 by jrummuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include <fcntl.h>
# include "libftprintf.h"
# include "op.h"
# include <stdint.h> //used for types in linux - remove before submitting the project

# define NOT_SET -1

extern unsigned char	g_arena[MEM_SIZE];
extern uint8_t			g_p_count;
extern uint64_t			g_dump_nbr;

typedef struct s_process t_process;

struct s_process
{
	uint8_t		instruction :5; //5-bit for 1-16 instruction
	uint8_t		carry :1; //one-bit var
	uint16_t	prog_counter; //current position
	uint16_t	bytes_to_next_instr;
	uint16_t	wait_cycle; //amount of waiting until executing $(instruction)
	uint32_t	process_id;
	uint32_t	last_live_cycle;
	uint32_t	reg[REG_NUMBER];
	t_process	*next;
};

typedef struct s_info
{
	t_process		*head;
} t_info;

//parse.c
void		parse(t_header_t *player, char **argv, int argc);

//player_handler.c
void		assign_player(t_header_t *player, unsigned char *file, int8_t p_num);
void		player_sort(t_header_t *player);

//error.c
void		check_file_size(uint32_t size);
void		check_file_type(unsigned char *file);
void		check_err_malloc(void *ptr);
void		print_man_page(void);
void		check_valid_arg(char **argv, int argc, uint8_t i);
void		check_existing_id(int8_t id);
void		check_missing_id(int8_t id);
void		check_num_within_range(uint8_t num);

//process.c
t_process	*new_process(t_process *head, uint16_t pos, int id);
void		process_init(t_header_t *player);

//utilities.c
int			get_4byte(unsigned char *size_byte);
void		initialize(t_header_t *player);

//corewar.c
void		corewar(t_header_t *player);

//test functions
void		print_mem(int size, unsigned char *mem);
void		print_process(t_process *process);
void		print_all_process(t_process *head);

#endif
