/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:48:56 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/30 23:16:37 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void	handle_label(int *tok_idx)
{
	t_token	*tokens;
	t_label	*current_label;
	t_file		*cor;

	cor = get_core_file();
	tokens = get_token_list()->tokens;
	current_label = retrieve_label(tokens[*tok_idx].content);
	current_label->idx = cor->idx;
	(*tok_idx)++;
}
	// ft_printf("label found: %s @%d\n", current_label->name, current_label->idx);
	// ft_printf("\tinstruction: %s\n", tokens[*tok_idx + 1].content);

unsigned int	hash(char *content)
{
	uint8_t				i;
	unsigned long long	res;

	i = 0;
	res = 0;
	while (content[i])
		res = res * 42 + content[i++];
	return ((unsigned int)(res % HASH_SIZE));
}

t_label	*retrieve_label(char *content)
{
	t_label	*temp;

	temp = get_labels()[hash(content)];
	while (temp)
	{
		if (!ft_strcmp(temp->name, content))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	add_label_list(char *content, t_token_type token_type)
{
	int			i;
	uint32_t	id;
	int		size;
	t_label		*current_label;

	size = ft_strlen(content);
	if (size > 0)
		size--;
	if (token_type == label)
		content[size] = '\0';
	else if (token_type == direct_label)
		ft_strcpy(content, &content[2]);
	else
		ft_strcpy(content, &content[1]);
	current_label = retrieve_label(content);
	if (!current_label)
		current_label = add_label(content);
	if (token_type == label)
		current_label->is_init = true;
}

// test
void	print_label()
{
	int	i;
	t_label	**labels;
	t_label	*temp;

	i = 0;
	labels = get_labels();
	while (i < HASH_SIZE)
	{
		if (labels[i])
		{
			ft_printf("%s\n", labels[i]->name);
			temp = labels[i]->next;
			while (temp)
			{
				ft_printf("%s\n", temp->name);
				temp = temp->next;
			}
		}
		i++;
	}
}

