/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:29:55 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/05 23:10:38 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void	handle_stay_p(char *stay_p, char *p, t_header_type type)
{
	if (type == name && (p - stay_p) < PROG_NAME_LENGTH)
		ft_memcpy(get_source()->name, &stay_p[1], (p - stay_p) - 1);
	else if (type == comment && (p - stay_p) < COMMENT_LENGTH)
		ft_memcpy(get_source()->comment, &stay_p[1],
			(p - stay_p) - 1);
	else
		ft_out("Error: Header too big");
}

char	*save_header_string(char *p, t_header_type type)
{
	char	*stay_p;

	stay_p = 0;
	while (1)
	{
		if (*p == '\"')
		{
			if (stay_p)
			{
				handle_stay_p(stay_p, p, type);
				break ;
			}
			stay_p = p;
		}
		else if ((*p != ' ' && *p != '\t' && !stay_p) || (*p == '\0'))
			ft_out("Error: Reading header");
		p++;
	}
	return (p + 1);
}

void	init_name_comment(void)
{
	get_source()->row = 2;
	get_source()->col = 0;
	ft_bzero(get_source()->name, PROG_NAME_LENGTH);
	ft_bzero(get_source()->comment, COMMENT_LENGTH);
}

char	*skip_comment(char	*p)
{
	while (*p != '\n' && *p != '\0')
		p++;
	p++;
	return (p);
}

char	*check_string_comment_name(bool	*is_newline, char *p)
{
	if (*p == '\t' || *p == ' ' || *p == '\n')
	{
		if (*p == '\n')
			*is_newline = true;
		p++;
	}
	else if (*p == '#' || *p == ';')
	{
		p = skip_comment(p);
		*is_newline = true;
	}
	else if (!ft_strncmp(NAME_CMD_STRING, p, 5))
	{
		p = save_header_string(&p[5], name);
		get_source()->save_name = true;
	}
	else if (!ft_strncmp(COMMENT_CMD_STRING, p, 8))
	{
		p = save_header_string(&p[8], comment);
		get_source()->save_comment = true;
	}
	else
		ft_out("Error: Reading header");
	return (p);
}
