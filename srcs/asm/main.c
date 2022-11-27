/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:29:55 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/27 19:46:00 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

uint8_t	*get_name(uint8_t*argc)
{
	int	len;
	int	name_len;
	uint8_t	*name;

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
	int		fd;
	uint8_t	*name;
	t_file	cor;

	cor_init(&cor, &name, &fd);
	write_header(&cor);
	write_intro(&cor);
	write_token(&cor);
	ft_printf("Writing output program to %s\n", name);
	write(fd, cor.str, cor.idx);
	free(cor.str);
}

int	main(int ac, char**av)
{
	init_parser();
	validate_argument(ac, av);
	parser(read_file(av[1]));
	token_check();
	label_list_check();
	things_into_bits();
	// print_tokens();
	return (0);
}

