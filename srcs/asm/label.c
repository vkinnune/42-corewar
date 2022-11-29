/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:48:56 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/29 16:54:24 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void	handle_label(t_file *cor, int *tok_idx)
{
/* 	t_token	*tokens;

	tokens = get_token_list()->tokens;
	save current cor.idx to hash table
	ft_printf("label found: %s @%d\n", tokens[*tok_idx].content, cor->idx); */
	(*tok_idx)++;
}

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

t_label	*new_label(char *content)
{
	t_label	*new;

	new = (t_label *)ft_memalloc(sizeof(t_label));
	new->name = ft_strdup(content);
	return (new);
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

t_label	*add_label(char *content)
{
	t_label	**head;
	t_label	*temp;

	head = &get_labels()[hash(content)];
	if (*head == NULL)
	{
		*head = new_label(content);
		return (*head);
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_label(content);
	return (temp->next);
}

void	add_label_list(char *content, t_token_type token_type)
{
	int			i;
	uint32_t	id;
	t_label		*current_label;

	if (token_type == label)
		content[ft_strlen(content) - 1] = '\0';
	else
		ft_strcpy(content, &content[2]);
	current_label = retrieve_label(content);
	if (!current_label)
		current_label = add_label(content);
	if (token_type == label)
		current_label->is_init = true;
}

void	label_list_error()
{
	int			i;
	t_label		*temp;
	t_label		**labels;

	i = 0;
	labels = get_labels();
	while (i < HASH_SIZE)
	{
		if (labels[i])
		{
			if (labels[i]->is_init == false)
				ft_out("ERROR ON LABELS");
			temp = labels[i]->next;
			while (temp)
			{
				if (temp->is_init == false)
					ft_out("ERROR ON LABELS");
				temp = temp->next;
			}
		}
		i++;
	}
}

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
