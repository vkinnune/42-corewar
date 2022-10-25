/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 23:13:47 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/26 01:10:47 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_failed_malloc(char ***arr, int i)
{
	if ((*arr)[i] == NULL)
	{
		ft_arrdel(arr);
		return (0);
	}
	return (1);
}

static void	move_to_char(const char *s, char *buf, t_index *i, char c)
{
	while ((s[i->str_idx] != c) && s[i->str_idx] != '\0')
		buf[i->buf_idx++] = s[i->str_idx++];
	buf[i->buf_idx] = '\0';
}

static int	protect_malloc(char **arr, char *buf)
{
	if (!arr || !buf)
	{
		if (arr)
			free(arr);
		if (buf)
			free(buf);
		return (0);
	}
	return (1);
}

char	**ft_strsplit(const char *s, char c)
{
	char	**arr;
	char	*buf;
	t_index	i;

	arr = (char **)ft_memalloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	buf = (char *)ft_memalloc(sizeof(char) * (ft_strlen(s) + 1));
	if (protect_malloc(arr, buf) == 0)
		return (NULL);
	i.str_idx = 0;
	i.arr_idx = 0;
	while (i.str_idx <= (int)ft_strlen(s))
	{
		i.buf_idx = 0;
		move_to_char(s, buf, &i, c);
		if (buf[0] != 0)
			arr[i.arr_idx++] = ft_strdup(buf);
		if (i.arr_idx > 0 && check_failed_malloc(&arr, i.arr_idx - 1) == 0)
			return (NULL);
		i.str_idx++;
	}
	free(buf);
	return (arr);
}
