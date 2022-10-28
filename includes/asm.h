/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:37:01 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/28 21:49:22 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# define MAX_TOKENS 100000
# define BUF_SIZE 100000

# include "libftprintf.h"
# include <fcntl.h>
# include "errors.h"

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

typedef struct s_token {
	t_token_type	type;
	char			*content;
	long int		 num;
}	t_token;

typedef struct s_token_list {
	t_token	tokens[MAX_TOKENS];
	int		token_count;
}	t_token_list;

typedef	struct s_parser {
	t_token_list	token_list;
}	t_parser;

#endif
