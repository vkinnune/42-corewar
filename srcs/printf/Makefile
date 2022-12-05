# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/24 10:35:47 by qnguyen           #+#    #+#              #
#    Updated: 2022/12/03 00:49:06 by qnguyen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../../libraries/libftprintf.a
LIBFT = ../../libraries/libft.a
LIBFT_DIR = ../libft/
SRCS = libftprintf prefix utilities utilities_2 printer flags_handler\
conversion_prefix_adapter init printf_d2base print_float extra
FLAGS = -Wall -Wextra -Werror
INCLUDES = ../../includes/
OBJS_DIR = ../../objs/ft_printf/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS)))

all: $(NAME)

$(NAME): $(OBJS)
	cp $(LIBFT) $(NAME)
	ar -rcs $(NAME) $(OBJS)

$(OBJS_DIR)%.o: %.c $(INCLUDES)libftprintf.h $(LIBFT)
	@mkdir -p $(OBJS_DIR)
	gcc -c $< $(FLAGS) -I$(INCLUDES) -o $@ #-O3 remove -O3 for linux

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJS_DIR)
	@/bin/rm -f $(OBJS)

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@/bin/rm -f a.out

re: fclean all

.PHONY: clean fclean all re
