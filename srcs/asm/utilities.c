/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:22:35 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/05 16:19:50 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static unsigned char	*get_name(unsigned char *argc)
{
	int				len;
	int				name_len;
	unsigned char	*name;

	len = ft_strlen((const char *)argc);
	while (len)
	{
		if (argc[len] == '.')
			break ;
		len--;
	}
	name_len = &argc[len] - argc;
	name = ft_memalloc(name_len + 5);
	check_err_malloc(name);
	ft_memcpy(name, argc, name_len);
	ft_memcpy(&name[name_len], ".cor", 5);
	return (name);
}

void	cor_init(unsigned char **name, int *fd)
{
	t_file	*cor;

	cor = get_core_file();
	cor->str = (unsigned char *)ft_memalloc(COR_FILE_SIZE);
	check_err_malloc(cor->str);
	cor->idx = 0;
	*name = get_name(get_source()->argc);
	*fd = open((const char *)*name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	check_open_error(*fd);
}

void	free_label(void)
{
	int		i;
	t_label	*temp;
	t_label	*next;
	t_label	**labels;

	i = 0;
	labels = get_labels();
	while (i < HASH_SIZE)
	{
		if (labels[i])
		{
			temp = labels[i]->next;
			while (temp)
			{
				free(temp->name);
				next = temp->next;
				free(temp);
				temp = next;
			}
			free(labels[i]->name);
			free(labels[i]);
		}
		i++;
	}
}
