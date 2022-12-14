/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:29:55 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/05 16:27:42 by vkinnune         ###   ########.fr       */
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
	write(1, g_p_str.s, g_p_str.i);
	write(fd, cor->str, file_size);
	close(fd);
	free(cor->str);
	free_label();
	free(name);
}

void	free_tokens(void)
{
	int				i;
	t_token_list	*token_list;

	i = 0;
	token_list = get_token_list();
	while (i != token_list->token_count)
	{
		free(token_list->tokens[i].content);
		i++;
	}
}

int	main(int ac, char**av)
{
	ft_bzero(get_parser(), sizeof(t_parser));
	validate_argument(ac, av);
	parser(read_file(av[1]));
	token_check();
	things_into_bits();
	free_tokens();
	return (0);
}
