/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lststrsplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:04:41 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/07 12:38:34 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lststrsplit(const char *s, char c)
{
	t_list	*lst;
	char	*buf;
	t_index	i;

	lst = NULL;
	buf = (char *)ft_memalloc(sizeof(char) * ft_strlen(s));
	if (buf == NULL)
		return (NULL);
	i.str_idx = 0;
	while (i.str_idx <= (int)ft_strlen(s))
	{
		i.buf_idx = 0;
		while ((s[i.str_idx] != c) && s[i.str_idx] != '\0')
			buf[i.buf_idx++] = s[i.str_idx++];
		buf[i.buf_idx] = '\0';
		if (buf[0] != '\0')
			ft_lstadd_back(&lst, ft_lstnew(buf, ft_strlen(buf) + 1));
		i.str_idx++;
	}
	free(buf);
	return (lst);
}
