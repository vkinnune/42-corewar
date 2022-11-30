/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:28:26 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/30 21:49:15 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

t_label	*new_label(char *content)
{
	t_label	*new;

	new = (t_label *)ft_memalloc(sizeof(t_label));
	new->name = ft_strdup(content);
	return (new);
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
	temp->next = new_label(content); // rev linked list cuz why not
	return (temp->next);			//the first one to be indexed remains the head
}

void	add_l_arg(t_token *toks, int instr_idx, int size)
{
	t_label_arg	*new;
	t_label_arg	**head;

	head = get_label_args();
	new = (t_label_arg *)ft_memalloc(sizeof(t_label_arg));
	new->token = toks;
	new->map_idx = get_core_file()->idx;
	new->instruct_idx = instr_idx;
	new->size = size;
	new->next = *head; //normal linked list
	*head = new;
}
