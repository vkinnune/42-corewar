/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:29:55 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/05 20:15:54 by vkinnune         ###   ########.fr       */
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
		if (((*p)[i] <= 'z' && (*p)[i] >= 'a') || (*p)[i] == '_'
				|| ((*p)[i] >= '0' && (*p)[i] <= '9'))
			i++;
		else
			return (0);
	}
}

int	get_size_of_instruction(char **p)
{
	int	size;

	size = 0;
	while ((*p)[size] != ' ' && (*p)[size]
			!= '\t' && (*p)[size] != '\n'
			&& (*p)[size] != '\0' && (*p)[size] != '%')
		size++;
	return (size);
}

int	instruction_check(char **p)
{
	int		i;
	int		size;
	bool	prcnt;

	i = 0;
	prcnt = false;
	size = get_size_of_instruction(p);
	if ((*p)[size] == '%')
		prcnt = true;
	while (i != INSTRUCTION_AMOUNT)
	{
		if (!ft_strncmp(op_tab[i].name, *p, size))
		{
			if (prcnt == true)
				size = ft_strlen(op_tab[i].name) - 1;
			else
				size = ft_strlen(op_tab[i].name);
			*p = &(*p)[size];
			get_source()->col += size;
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
