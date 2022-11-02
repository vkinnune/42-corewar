/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:32:42 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/02 18:58:30 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include <fcntl.h>
# include "libftprintf.h"
# include "op.h"
# include <stdint.h> //used for types in linux - remove before submitting the project

# define NOT_SET	42
# define EI_KIITOS	-1
# define DAIJOBU	1

typedef struct s_process t_process;
typedef struct s_game_param	t_game_param;
typedef struct s_flag t_flag;
typedef struct s_arg t_arg;

struct s_process
{
	uint8_t		instruction :5; //5-bit for instruction 1-16
	uint8_t		carry :1; //one-bit var
	uint16_t	prog_counter; //current position
	uint16_t	bytes_to_next_instr;
	uint16_t	wait_cycle; //amount of waiting until executing $(instruction)
	// uint32_t	process_id;
	uint32_t	last_live_cycle;
	uint32_t	reg[REG_NUMBER];
	t_process	*next;
};

struct s_game_param
{
	uint8_t		check_counter;
	uint8_t		last_alive;
	uint16_t	cycle_to_die;
	uint32_t	live_performed;
	uint64_t	current_cycle;
	t_process	*head;
};

struct s_arg
{
	uint8_t		arg_type;
	uint32_t	value;
};


enum registry
{
	r1 = 1,
	r2,
	r3,
	r4,
	r5,
	r6,
	r7,
	r8,
	r9,
	r10,
	r11,
	r12,
	r13,
	r14,
	r15,
	r16
};

struct s_flag
{
	int8_t	id;
	uint8_t	byte;
	int64_t	dump_nbr;
};

extern unsigned char	g_arena[MEM_SIZE];
extern uint8_t			g_p_count;
extern int64_t			g_dump_nbr;
extern enum registry	reg;

//parse.c
void		parse(t_header_t *player, char **argv, int argc, t_flag *flags);

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
void		processor(t_game_param *game);

//process_util.c
void		delete_process(t_process *prev, t_process *delete);
t_process	*new_process(t_process *head, uint16_t pos, int id);
t_process	*process_init(t_header_t *player);
void		process_kill(t_game_param *game);

//utilities.c
int			get_n_byte(uint8_t n, unsigned char *size_byte);
uint8_t		get_2bit(uint8_t byte, uint8_t position);
void		initialize(t_header_t *player);

//corewar.c
void		corewar(t_header_t *player, t_flag *flags);

//game.c
void		vm(t_header_t *player, t_process *head, t_flag *flag);

//instruction.c

//instruc_util.c
uint8_t		check_matching_arg(t_process *process, t_arg *arg);
int8_t		assign_arg_value(t_arg *arg, t_process *process);
void		casting(t_arg *arg);

//test functions
void		print_mem(int size, unsigned char *mem);
void		print_process(t_process *process);
void		print_all_process(t_process *head);
void		print_arena(t_header_t *player, t_flag *flags);
void		print_arg(t_process *process, t_arg *arg);

#endif
