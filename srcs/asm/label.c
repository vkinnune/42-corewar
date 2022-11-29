/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:48:56 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/29 12:31:28 by qnguyen          ###   ########.fr       */
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

t_label	*retrieve_label(char *content)
{
	t_label	*temp;

	temp = get_label_list()->labels[hash(content)];
	while (temp)
	{
		if (!ft_strcmp(temp->name, content))
			return (temp);
		temp = temp->next;
	}
	return(NULL);
}

t_label	*retrieve_handle_collision(char *content)
{
	t_label	**head;
	t_label	*temp;
	t_label	*last_slot;

	head = &get_label_list()->labels[hash(content)];
	temp = *head;
	last_slot = 0;
	while (temp)
	{
		if (!ft_strcmp(temp->name, content))
			return (temp);
		last_slot = temp;
		temp = temp->next;
	}
	temp = (t_label *)ft_memalloc(sizeof(t_label));
	temp->name = ft_strdup(content);
	if (last_slot)
		last_slot->next = temp;
	else
		*head = temp;
	return (temp);
}

void	add_label_list(char *content, t_token_type token_type)
{
	int				i;
	uint32_t		id;
	t_label_list	*label_list;

	if (token_type == label)
		content[ft_strlen(content) - 1] = '\0';
	else
		ft_strcpy(content, &content[2]);
	if (token_type == label)
		retrieve_handle_collision(content)->is_init = true;
}

void	label_list_error()
{
	int				i;
	t_label_list	*label_list;

	i = 0;
	label_list = get_label_list();
	while (i != label_list->label_count)
	{
		if (label_list->labels[i]->is_init == false)
			ft_out("ERROR ON LABELS");
		i++;
	}
}
