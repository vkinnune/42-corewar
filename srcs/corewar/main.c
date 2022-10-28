/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:10:51 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/28 23:27:15 by jrummuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	print_man_page(void)
{
	ft_printf("man page goes here\n");
	exit(0);
}
			//THESE 2 DIDNT WORK
//void	process_values(t_process **new_process, unsigned int pos, t_header_t player, int id)
//{
//	int i;
//
//	i = 0;
//	(*new_process)->process_id = id;
//	(*new_process)->prog_counter = pos;
//	(*new_process)->carry = 0;
//	(*new_process)->instruction = 0;
//	(*new_process)->last_live_cycle = 0;
//	(*new_process)->bytes_to_next_instr = 0;
//	(*new_process)->wait_cycle = 0; //amount of waiting until executing $(instruction)
//	while (i < REG_NUMBER)
//		(*new_process)->reg[i++] = 0;
//	(*new_process)->next = NULL; 
//}
//
//t_process *process_init(unsigned char *pos, t_header_t player, int id)
//{
//	int i;
//	t_process *new_process;
//
//	i = 0;
//	new_process = (t_process *)malloc(sizeof(t_process));
//	if (!new_process)
//	{
//		ft_printf("senpai, there was error allocating carriage, UwU\n");
//		exit(-1);
//	}
//	process_values(&new_process,(unsigned int) pos, player, id);
//	return(new_process);
//}

void	set_processes(t_process **new_process, unsigned int pos, int id)
{
	int i;

	i = 0;
	(*new_process)->process_id = id;
	(*new_process)->prog_counter = pos;
	(*new_process)->carry = 0;
	(*new_process)->instruction = 0;
	(*new_process)->last_live_cycle = 0;
	(*new_process)->bytes_to_next_instr = 0;
	(*new_process)->wait_cycle = 0; //amount of waiting until executing $(instruction)
	while (i < REG_NUMBER)
		(*new_process)->reg[i++] = 0;
	(*new_process)->next = NULL; 
}

void	process_init(unsigned char *arena, t_header_t *player, int p_count)
{
	int i;
	int p_start;
	t_info *info;
	t_process *new_process;
	t_process *prev;

	prev = NULL;
	info = malloc(sizeof(t_info));
	i = 0;
	p_start = 0;
	while (i < p_count)
	{
		new_process = (t_process *)malloc(sizeof(t_process));
		if (!new_process)
		{
			ft_printf("UwU, there was problem with allocating process\n");
			exit(1);
		}
		set_processes(&new_process, (arena + p_start) - arena, i);
		new_process->next = prev;
		prev = new_process;
		info->head = new_process;
		p_start += MEM_SIZE / p_count;
		i++;
	}
	new_process = info->head;
	while(new_process)
	{
		ft_printf("in list id: %d pos: %d\n", new_process->process_id, new_process->prog_counter);
		new_process = new_process->next;
	}
}

void	arena_init(unsigned char *arena, t_header_t *player, int p_count)
{
	int	i;
	int	p_start;

	ft_bzero((void *)arena, MEM_SIZE);
	i = 0;
	p_start = 0;
	while (i < p_count)
	{
		ft_memcpy(arena + p_start, player[i].code, player[i].prog_size);
		p_start += MEM_SIZE / p_count;
		i++;
	}
}

int	main(int argc, char **argv)
{
	int				i;
	int				p_count;
	t_header_t		player[4];
	unsigned char	arena[MEM_SIZE];

	if (argc < 2)
		print_man_page();
	i = 1;
	while (i < argc)
	{
		p_count = parse(player, argv[i]);
		i++;
	}
//	print_mem(player[0].prog_size, player[0].code);
	arena_init(arena, player, p_count);
	process_init(arena, player, p_count);
	print_mem(MEM_SIZE, arena);
	return (0);
}
