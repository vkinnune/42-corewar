/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:32:42 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/17 20:00:25 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include <fcntl.h>
# include "libftprintf.h"
# include "op.h"
# include <stdint.h> //used for types in linux - remove before submitting the project

# define NOT_SET	0
# define SET		1
# define NOT_OKEI	0
# define OKEI		1

typedef struct	s_process t_process;
typedef struct 	s_game_param	t_game_param;
typedef struct	s_flag t_flag;
typedef struct 	s_arg t_arg;
typedef void	t_instruct_table(t_process *process, t_arg *arg, t_game_param *game);
typedef void	t_verbose_table(t_process *process, t_arg *arg, t_game_param *game);
typedef struct	s_table t_table;

struct s_process
{
	int8_t		cmd :5; //5-bit for instruction 1-16
	uint8_t		carry :1; //one-bit var
	uint16_t	pc; //current position
	uint16_t	bytes_to_next;
	uint16_t	wait_cycle; //amount of waiting until executing $(instruction)
	uint32_t	id; //this is used to know which one we're looking at when testing
	uint32_t	last_live_cycle;
	uint32_t	reg[REG_NUMBER + 1]; //reg[0] will store nothing, r1 == 1
	t_process	*next;
};

struct s_game_param
{
	uint8_t		check_counter;
	uint8_t		last_alive;
	int16_t		cycle_to_die;
	uint32_t	live_performed;
	uint64_t	current_cycle;
	t_process	*head;
};

struct s_arg
{
	uint8_t		type;
	int32_t		value;
};

struct s_flag
{
	int8_t		id;
	int8_t		aff;
	uint8_t		byte;
	uint8_t		verbose;
	uint64_t	dump_nbr;
};

struct s_table
{
	t_instruct_table	*instruct_table[16];
	t_verbose_table		*verbose_table[16];
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

extern unsigned char	g_arena[MEM_SIZE];
extern uint8_t			g_p_count;
extern int64_t			g_dump_nbr;
extern enum registry	reg;
extern t_flag			g_flags;

//parse.c
void		parse(t_header_t *player, char **argv, int argc);

//player_handler.c
void		assign_player(t_header_t *player, unsigned char *file, int8_t p_num, uint16_t ret);
void		player_sort(t_header_t *player);

//error.c
void		check_file_type(unsigned char *file, int16_t fd);
void		check_file_size(uint32_t size);
void		check_matching_champ_size(uint32_t byte_size, uint32_t actual);
void		check_err_malloc(void *ptr);
void		print_man_page(void);
void		check_valid_arg(char **argv, int argc, uint8_t i);
void		check_existing_id(int8_t id);
void		check_missing_id(int8_t id);
void		check_num_within_range(uint8_t num);

//process.c
void		processor(t_game_param *game, t_table *tab, t_header_t *player);

//process_util.c
void		free_process(t_process *prev, t_process *delete);
void		free_all_process(t_process *head);
t_process	*new_process(t_process *head, uint16_t pos, int id);
t_process	*process_init(t_header_t *player);
void		kill_process(t_game_param *game);
void		get_arg_without_arg_byte(t_process *process, t_arg *arg);

//utilities.c
int			get_n_byte(uint8_t n, unsigned char *data, uint32_t idx);
uint8_t		get_2bit(uint8_t byte, uint8_t position);
uint32_t	get_2hext(uint32_t num, uint8_t position);

//corewar.c
void		corewar(t_header_t *player);

//instruction.c
void		live(t_process *process, t_arg *arg, t_game_param *game);
void		l_ld(t_process *process, t_arg *arg, t_game_param *game);
void		st(t_process *process, t_arg *arg, t_game_param *game);
void		add_sub(t_process *process, t_arg *arg, t_game_param *game);
void		and_or_xor(t_process *process, t_arg *arg, t_game_param *game);
void		zjmp(t_process *process, t_arg *arg, t_game_param *game);
void		l_ldi(t_process *process, t_arg *arg, t_game_param *game);
void		sti(t_process *process, t_arg *arg, t_game_param *game);
void		l_foork(t_process *process, t_arg *arg, t_game_param *game);
void		aff(t_process *process, t_arg *arg, t_game_param *game);

//verbose_two.c
void		verbose_live(t_process *process, t_arg *arg, t_game_param *game);
void		verbose_l_ld(t_process *process, t_arg *arg, t_game_param *game);
void		verbose_st(t_process *process, t_arg *arg, t_game_param *game);
void		verbose_add_sub(t_process *process, t_arg *arg, t_game_param *game);
void		verbose_and_or_xor(t_process *process, t_arg *arg, t_game_param *game);
void		verbose_zjmp(t_process *process, t_arg *arg, t_game_param *game);
void		verbose_l_ldi(t_process *process, t_arg *arg, t_game_param *game);
void		verbose_sti(t_process *process, t_arg *arg, t_game_param *game);
void		verbose_l_foork(t_process *process, t_arg *arg, t_game_param *game);
void		verbose_aff(t_process *process, t_arg *arg, t_game_param *game);

//instruc_util.c
int32_t	get_arg_value(t_process *process, t_arg *arg);
int8_t		check_matching_arg(t_process *process, t_arg *arg, t_game_param *game);
// int8_t		check_matching_arg(t_process *process, t_arg *arg);
void		write_4byte(t_process *process, uint32_t value, uint16_t position);
uint16_t	get_position(uint16_t pos);

//init.c
void		initialize_players(t_header_t *player);
void		arena_init(t_header_t *player);
void		game_init(t_game_param *game, t_process *head);
void		flag_init();

//print.c
void		print_arena(t_header_t *player);
void		print_arg(t_process *process, t_arg *arg);
#endif
