/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:29:55 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/29 11:45:06 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void	things_into_bits(void)
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
	things_into_bits();
	print_tokens();
	return (0);
}

