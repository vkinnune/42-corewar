/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:29:55 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/02 18:10:16 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void	things_into_bits(void)
{
	int		fd;
	int		file_size;
	t_file	*cor;
	uint8_t	*name;

	cor_init(&name, &fd);
	cor = get_core_file();
	write_token();
	file_size = cor->idx;
	write_label();
	write_header();
	write_intro(file_size - EXEC_CODE_POSITION);
	ft_printf("Writing output program to %s\n", name);
	write(fd, cor->str, file_size);
	close(fd);
	free(cor->str);
}

int	main(int ac, char**av)
{
	ft_bzero(get_parser(), sizeof(t_parser));
	validate_argument(ac, av);
	parser(read_file(av[1]));
	token_check();
	things_into_bits();
	// print_tokens();
	// print_label();
	return (0);
}
