/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:29:55 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/09 16:06:44 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*get_name(char *argc)
{
	int	len;
	int	name_len;
	char	*name;

	len = ft_strlen(argc);
	while (len)
	{
		if (argc[len] == '.')
			break ;
		len--;
	}
	name_len = &argc[len] - argc;
	name = ft_memalloc(name_len + 5);
	ft_memcpy(name, argc, name_len);
	ft_memcpy(&name[name_len], ".cor", 5);
	return (name);
}

void	things_into_bits()
{
	int	fd;
	char	*name;

	name = get_name(get_source()->argc);
	fd = open(name, O_WRONLY | O_APPEND | O_CREAT, 0644);
}

int	main(int ac, char **av)
{
	init_parser();
	validate_argument(ac, av);
	parser(read_file(av[1]));
	token_check();
	label_list_check();
	things_into_bits();
	print_tokens();
	return (0);
}

