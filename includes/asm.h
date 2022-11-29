/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:37:01 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/29 19:28:46 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# define MAX_TOKENS 100000
// # define MAX_LABELS 100000
# define BUF_SIZE 100000
# define COR_FILE_SIZE 1000000
# define INSTRUCTION_AMOUNT 16
# define HASH_SIZE 5000
# define LABEL_EXIST 1
# define LABEL_NO_EXIST 0
# include "libftprintf.h"
# include <fcntl.h>
# include "errors.h"
# include <stdio.h>
# include <stdbool.h>
# include "op.h"

// typedef uint8_t	t_arg_func(t_file *cor, int arg_i, int op_size, uint8_t *data);
typedef struct s_label t_label;
typedef struct s_label_arg t_label_arg;

typedef enum	e_token_type
{
	label,	//loop:
	instruction,	//sti
	reg,	//r1
	separator, //,
	direct_label, //%: live
	direct, //% 1
	indirect, //1
	indirect_label //: live
}	t_token_type;

typedef enum	e_header_type
{
	name,
	comment
}	t_header_type;

typedef struct s_token {
	t_token_type	type;
	char			*content;
}	t_token;

typedef struct s_token_list {
	int		token_count;
	t_token	tokens[MAX_TOKENS];
}	t_token_list;

typedef struct s_source {
	int				col;
	int				row;
	unsigned char	*argc;
	char			name[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
	bool			label;
	bool			ins;
}	t_source;

struct s_label
{
	bool			is_init;
	unsigned int	idx;
	char			*name;
	t_label			*next;
};

struct s_label_arg
{
	uint8_t		size :3;
	int			map_idx; //where to write the bytes to
	int			instruct_idx;
	t_token		*token;
	t_label_arg	*next;
};

typedef	struct s_parser {
	t_token_list	token_list;
	t_source		source;
	t_label			*labels[HASH_SIZE];
}	t_parser;

void	validate_argument(int ac, char **av);

t_parser	*get_parser(void);
void	init_parser();
void	parser(const char *input);
char	*read_file(char *file_name);
void	print_tokens();
t_token_list	*get_token_list();
t_label	**get_labels();
t_label_arg	**get_label_args(void);
void	token_check();
t_source	*get_source();
t_file	*get_core_file(void);
int	label_check(char **p);
int	instruction_check(char **p);
int	register_check(char **p);
int	separator_check(char **p);
int direct_label_check(char **p);
int	direct_check(char **p);
char	*handle_header(const char *input);
void	handle_asm(char *p);
void	save_token(char **p, char *old_p, t_token_type token_type);

//label.c
void	add_label_list(char *content, t_token_type token_type);
void	label_list_error();
t_label	*retrieve_label(char *content);

//instruction_handler.c
void	handle_instruction(int *tok_idx);
uint8_t	lab_arg(int instr_idx, int arg_i, int op_size, t_token *toks);
uint8_t	dir_arg(int arg_i, int op_size, t_token *toks);
uint8_t	ind_arg(int arg_i, t_token *toks);
uint8_t	reg_arg(int arg_i, t_token *toks);

//label.c
unsigned int	hash(char *content);
void			handle_label(int *tok_idx);
void			print_label();
t_label_arg	*new_l_arg(t_token *tok, int map_idx, int inst_idx, uint8_t d_size);

//error.c
void	check_open_error(int fd);

//write.c
void	write_header();
void	write_intro();
void	write_token();

//utilities.c
void	cor_init(uint8_t **name, int *fd);
// void	arg_func_init(t_arg_func **arg_funcs);
#endif
