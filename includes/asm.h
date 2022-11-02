/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:37:01 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/31 15:07:14 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# define MAX_TOKENS 100000
# define BUF_SIZE 100000
# define NAME_SIZE 64
# define COMMENT_SIZE 64

# include "libftprintf.h"
# include <fcntl.h>
# include "errors.h"
# include <stdio.h>
# include <stdbool.h>

void	validate_argument(int ac, char **av);

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
	long int		 num;
}	t_token;

typedef struct s_token_list {
	t_token	tokens[MAX_TOKENS];
	int		token_count;
}	t_token_list;

typedef struct s_source {
	int		col;
	int		row;
	char	name[NAME_SIZE];
	char	comment[COMMENT_SIZE];
	char	*ins[16][7];
}	t_source;

typedef	struct s_parser {
	t_token_list	token_list;
	t_source		source;
}	t_parser;

#endif

