/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:29:55 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/02 17:34:49 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

int	indirect_check(char **p)
{
	int	i;

	i = 0;
	if (**p == '-')
		i++;
	while (ft_isdigit((*p)[i]))
		i++;
	if ((i == 1 && **p == '-') || i == 0)
		return (0);
	get_source()->col += i - 1;
	*p = &(*p)[i - 1];
	return (1);
}

int	indirect_label_check(char **p)
{
	int	i;

	i = 2;
	if ((*p)[0] == ':')
	{
		while (ft_isprint((*p)[i]) && (*p)[i] != ','
			&& (*p)[i] != ' ' && (*p)[i] != '\t' && (*p)[i] != '\n')
			i++;
		if (i > 1)
		{
			get_source()->col += (i - 1);
			*p = &(*p)[i - 1];
			return (1);
		}
	}
	return (0);
}

int	check_valid(char **p)
{
	t_token_type	token_type;
	char			*old_p;

	old_p = *p;
	if (get_source()->label == false && label_check(p))
		token_type = label;
	else if (get_source()->ins == false && instruction_check(p))
		token_type = instruction;
	else if (register_check(p))
		token_type = reg;
	else if (separator_check(p))
		token_type = separator;
	else if (direct_label_check(p))
		token_type = direct_label;
	else if (direct_check(p))
		token_type = direct;
	else if (indirect_check(p))
		token_type = indirect;
	else if (indirect_label_check(p))
		token_type = indirect_label;
	else
		return (0);
	save_token(p, old_p, token_type);
	return (1);
}

int	move_forward(char **p)
{
	t_source	*source;

	source = get_source();
	if (**p == '\n')
	{
		source->ins = false;
		source->label = false;
		source->row++;
		source->col = 0;
	}
	else if (**p == '\0')
		return (0);
	else
		source->col++;
	(*p)++;
	return (1);
}

void	handle_asm(char *p)
{
	while (move_forward(&p))
	{
		if (*p == ' ' || *p == '\t' || *p == '\n')
			continue ;
		else if (*p == '\0')
			break ;
		if (*p == '#')
			while (*p != '\n' && *p != '\0')
				p++;
		else if (!check_valid(&p))
		{
			ft_printf("Error in col: %d row: %d",
				get_source()->col, get_source()->row);
			exit(EXIT_FAILURE);
		}
	}
}

