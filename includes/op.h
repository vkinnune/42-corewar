/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2022/12/01 20:45:42 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

#ifndef OP_H
# define OP_H

# define IND_SIZE			2
# define REG_SIZE			4
# define DIR_SIZE			REG_SIZE

# define REG_NAME_SIZE		1

# define REG_CODE			0b01 //1
# define DIR_CODE			0b10 //2
# define IND_CODE			0b11 //3

# define MAX_ARGS_NUMBER	4
# define MAX_PLAYERS		4
# define MEM_SIZE			4096 //(4*1024)
# define IDX_MOD			512 //(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE		682 //(MEM_SIZE / 6)

# define COMMENT_CHAR		'#'
# define ALT_COMMENT_CHAR	';'
# define LABEL_CHAR			':'
# define DIRECT_CHAR		'%'
# define SEPARATOR_CHAR		','

# define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRING	".comment"

# define REG_NUMBER			16

# define CYCLE_TO_DIE		1536
# define CYCLE_DELTA		50
# define NBR_LIVE			21
# define MAX_CHECKS			10

/*
**
*/

typedef char	t_arg_type;

# define T_REG				0b001 //1
# define T_DIR				0b010 //2
# define T_IND				0b100 //4

# define T_LAB				8

/*
**
*/

# define PROG_NAME_LENGTH	(128)
# define COMMENT_LENGTH		(2048)
# define COREWAR_EXEC_MAGIC	0xea83f3

typedef struct s_header_s
{
	uint8_t			id;
	unsigned int	magic;
	unsigned int	prog_size;
	unsigned char	prog_name[PROG_NAME_LENGTH + 1];
	unsigned char	comment[COMMENT_LENGTH + 1];
	unsigned char	*code;
}			t_header_t;

typedef struct s_op
{
	char			name[6];
	uint8_t			arg_amt :2;
	uint8_t			arg_type[3];
	uint8_t			order_num :5;
	uint16_t		wait_cycle;
	char			*description;
	uint8_t			arg_byte :1;
	uint8_t			dir_size :1;
}				t_op;

typedef struct s_file
{
	unsigned char	*str;
	uint32_t		idx;
}				t_file;
extern t_op				op_tab[17];

//shared_util.c
uint32_t	get_2hext(uint32_t num, uint8_t position, uint8_t n);
void	write_n_byte(t_file *file, uint32_t val
		, uint16_t get_pos(uint16_t), int8_t n);
#endif
