/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:37:01 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/29 16:44:08 by qnguyen          ###   ########.fr       */
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

typedef struct s_label {
	char	*name;
	// unsigned int	idx;
	bool			is_init;
	struct s_label	*next;
}	t_label;

typedef	struct s_parser {
	t_token_list	token_list;
	t_source		source;
	t_label			*labels[HASH_SIZE];
}	t_parser;

void	validate_argument(int ac, char **av);

void	init_parser();
void	parser(const char *input);
char	*read_file(char *file_name);
void	print_tokens();
t_token_list	*get_token_list();
t_label	**get_labels();
void	token_check();
t_source	*get_source();

//label.c
void	add_label_list(char *content, t_token_type token_type);
void	label_list_error();
t_label	*retrieve_label(char *content);

//instruction_handler.c
void	handle_instruction(t_file *cor, int *tok_idx);
uint8_t	lab_arg(t_file *cor, int arg_i, int op_size, char *content);
uint8_t	dir_arg(t_file *cor, int arg_i, int op_size, char *content);
uint8_t	ind_arg(t_file *cor, int arg_i, int op_size, char *content);
uint8_t	reg_arg(t_file *cor, int arg_i, int op_size, char *content);

//label.c
unsigned int	hash(char *content);
void	handle_label(t_file *cor, int *tok_idx);
void	print_label();

//error.c
void	check_open_error(int fd);

//write.c
void	write_header(t_file *cor);
void	write_intro(t_file *cor);
void	write_token(t_file *cor);

//utilities.c
void	cor_init(t_file *cor, uint8_t **name, int *fd);
// void	arg_func_init(t_arg_func **arg_funcs);
#endif
