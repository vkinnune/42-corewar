/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:28:26 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/05 16:28:12 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

t_label	*new_label(char *content)
{
	t_label	*new;

	new = (t_label *)ft_memalloc(sizeof(t_label));
	check_err_malloc(new);
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
	temp->next = new_label(content);
	return (temp->next);
}

void	add_l_arg(t_token *toks, int instr_idx, int size)
{
	t_label_arg	*new;
	t_label_arg	**head;

	head = get_label_args();
	new = (t_label_arg *)ft_memalloc(sizeof(t_label_arg));
	check_err_malloc(new);
	new->token = toks;
	new->map_idx = get_core_file()->idx;
	new->instruct_idx = instr_idx;
	new->size = size;
	new->next = *head;
	*head = new;
}
