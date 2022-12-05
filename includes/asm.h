/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:37:01 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/05 16:34:16 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# define MAX_TOKENS 100000
# define BUF_SIZE 100000
# define COR_FILE_SIZE 1000000
# define INSTRUCTION_AMOUNT 16
# define HASH_SIZE 5000
# define LABEL_EXIST 1
# define LABEL_NO_EXIST 0
# define EXEC_CODE_POSITION 2192
# include "libftprintf.h"
# include <fcntl.h>
# include "errors.h"
# include <stdio.h>
# include <stdbool.h>
# include "op.h"

typedef struct s_label t_label;
typedef struct s_label_arg t_label_arg;

typedef enum	e_token_type
{
	label,
	instruction,
	reg,
	separator,
	direct_label,
	direct,
	indirect,
	indirect_label
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
	uint8_t			size :3;
	int				map_idx;
	unsigned int	instruct_idx;
	t_token			*token;
	t_label_arg		*next;
};

typedef	struct s_parser {
	t_token_list	token_list;
	t_source		source;
	t_label			*labels[HASH_SIZE];
}	t_parser;

void	validate_argument(int ac, char **av);

t_parser	*get_parser(void);
void	init_parser();
void	parser(char *input);
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
int	check_instruction(int *i, t_token_list *token_list);

//label.c
void			handle_label(int *tok_idx);
unsigned int	hash(char *content);
t_label			*retrieve_label(char *content);
void			add_label_list(char *content, t_token_type token_type);
void			label_list_error();
void			print_label();

//label_utils.c
t_label		*add_label(char *content);
void		add_l_arg(t_token *toks, int instr_idx, int size);

//instruction_handler.c
void	handle_instruction(int *tok_idx);

//arg_handler.c
uint8_t	lab_arg(t_token *toks, int instr_idx, int arg_i, int op_size);
uint8_t	dir_arg(t_token *toks, int arg_i, int op_size);
uint8_t	ind_arg(t_token *toks, int arg_i);
uint8_t	reg_arg(t_token *toks, int arg_i);

//error.c
void	check_open_error(int fd);

//write.c
void	write_header(void);
void	write_intro(uint32_t champ_size);
void	write_token(void);
void	write_label(void);

//utilities.c
void	cor_init(uint8_t **name, int *fd);
void	free_label(void);
void	free_label_arg(void);
#endif

