/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:29:55 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/29 21:02:48 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void	things_into_bits(void)
{
	int		fd;
	t_file	*cor;
	uint8_t	*name;

	cor_init(&name, &fd);
	// write_header();
	// write_intro();
	write_token();
	//write_label();
	// ft_printf("Writing output program to %s\n", name);
	cor = get_core_file();
	write(fd, cor->str, cor->idx);
	free(cor->str);
}

int	main(int ac, char**av)
{
	ft_bzero(get_parser(), sizeof(t_parser));
	validate_argument(ac, av);
	parser(read_file(av[1]));
	token_check();
	things_into_bits();
	// print_label();
	// print_tokens();
	return (0);
}
