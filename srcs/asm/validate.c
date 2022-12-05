/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:59:59 by vkinnune          #+#    #+#             */
/*   Updated: 2022/12/05 16:19:20 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	is_dot_s(char *av)
{
	int	len;

	len = ft_strlen(av);
	while (len)
	{
		if (!ft_strncmp(&av[len - 1], ".s\0", 3))
			break ;
		len--;
	}
	if (len == 0)
		return (0);
	else
		return (1);
}

void	validate_argument(int ac, char **av)
{
	if (ac == 2 && is_dot_s(av[1]))
	{
		get_source()->argc = (unsigned char *)av[1];
		return ;
	}
	else if (ac == 2)
	{
		ft_out(INVALID_FILE_TYPE);
	}
	else
		ft_out(USAGE);
}
