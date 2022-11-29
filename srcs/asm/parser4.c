/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:29:55 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/28 18:12:39 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

int	label_check(char **p)
{
	int	i;

	i = 0;
	while (1)
	{
		if ((*p)[i] == ':' && i > 0)
		{
			*p = &(*p)[i + 1];
			get_source()->col += i + 1;
			get_source()->label = true;
			return (1);
		}
		else if ((*p)[i] == '\n' || (*p)[i] == '\0'
			|| (*p)[i] == ' ' || (*p)[i] == '\t' || (*p)[i] == '%')
			return (0);
		if (ft_isascii((*p)[i]))
			i++;
		else
			return (0);
	}
}

int	instruction_check(char **p)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while ((*p)[size] != ' ' && (*p)[size] != '\t')
		size++;
	while (i != INSTRUCTION_AMOUNT)
	{
		if (!ft_strncmp(op_tab[i].name, *p, size))
		{
			*p = &(*p)[ft_strlen(op_tab[i].name)];
			get_source()->col += ft_strlen(op_tab[i].name);
			get_source()->ins = true;
			return (1);
		}
		i++;
	}
	return (0);
}

int	register_check(char **p)
{
	int	i;

	if (**p == 'r')
	{
		i = 1;
		while (1)
		{
			if (ft_isdigit((*p)[i]))
				i++;
			else if (i > 1)
			{
				*p = &(*p)[i - 1];
				get_source()->col += (i - 1);
				return (1);
			}
			else
				break ;
		}
	}
	return (0);
}

int	separator_check(char **p)
{
	if (**p == ',')
		return (1);
	else
		return (0);
}

int	direct_label_check(char **p)
{
	int	i;

	i = 2;
	if ((*p)[0] == '%' && (*p)[1] == ':')
	{
		while (ft_isprint((*p)[i]) && (*p)[i] != ','
			&& (*p)[i] != ' ' && (*p)[i] != '\t' && (*p)[i] != '\n')
			i++;
		if (i > 2)
		{
			get_source()->col += (i - 1);
			*p = &(*p)[i - 1];
			return (1);
		}
	}
	return (0);
}

