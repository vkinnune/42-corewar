/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:37:01 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/27 14:45:47 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# define MAX_TOKENS 100000
# define MAX_LABELS 100000
# define BUF_SIZE 100000
# define COR_FILE_SIZE 1000000
# define INSTRUCTION_AMOUNT 16

# include "libftprintf.h"
# include <fcntl.h>
# include "errors.h"
# include <stdio.h>
# include <stdbool.h>
# include "op.h"

typedef enum	e_token_type
{
	label,	//loop:
	instruction,	//sti
	reg,	//r1
	separator, //,
	direct_label, //%: live
	direct, //% 1
	indirect //1
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
	int		col;
	int		row;
	char	*argc;
	char	name[PROG_NAME_LENGTH];
	char	comment[COMMENT_LENGTH];
	bool	label;
	bool	ins;
}	t_source;

typedef struct s_label {
	unsigned int		id;
	bool	is_init;
}	t_label;

typedef struct s_label_list {
	int		label_count;
	t_label	labels[MAX_LABELS];
}	t_label_list;

typedef	struct s_parser {
	t_token_list	token_list;
	t_source	source;
	t_label_list	label_list;
}	t_parser;

void	validate_argument(int ac, char **av);

void	init_parser();
void	parser(const char *input);
char	*read_file(char *file_name);
void	print_tokens();
t_token_list	*get_token_list();
t_label_list	*get_label_list();
void	token_check();
void	label_list_check();
t_source	*get_source();

//instruction_handler.c
void	handle_instruction(t_file *cor, int *tok_idx);
void	handle_label(int *tok_idx);

//error.c
void	check_open_error(int fd);

//write.c
void	write_intro(t_file *cor);
void	write_token(t_file *cor);
#endif
