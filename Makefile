# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 23:59:55 by qnguyen           #+#    #+#              #
#    Updated: 2022/10/30 19:22:28 by qnguyen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COR_NAME = corewar
COR_DIR = srcs/corewar/
# add new .c files here
COR_FILE = main player_handler error utilities parse process
COR_OBJS_DIR = objs/corewar/
COR_OBJS = $(addprefix $(COR_OBJS_DIR), $(addsuffix .o, $(COR_FILE)))

ASM_NAME = asm
ASM_DIR = srcs/asm/
# add new .c files here
ASM_FILE = main validate
ASM_OBJS_DIR = objs/asm/
ASM_OBJS = $(addprefix $(ASM_OBJS_DIR), $(addsuffix .o, $(ASM_FILE)))

PRINTF = libraries/libftprintf.a
PRINTF_DIR = srcs/printf/

FLAG = -Wall -Werror -Wextra
INCLUDES = -I includes

all: $(COR_NAME) $(ASM_NAME)

################ COREWAR ################

$(COR_NAME): $(COR_OBJS) includes/corewar.h $(PRINTF)
	gcc $(COR_OBJS) $(INCLUDES) $(PRINTF) -o $@

$(COR_OBJS_DIR)%.o: $(COR_DIR)%.c
	@mkdir -p $(COR_OBJS_DIR)
	gcc -g -c $< $(INCLUDES) -o $@

################ ASM ################

$(ASM_NAME): $(ASM_OBJS) $(PRINTF)
	gcc $(ASM_OBJS) $(INCLUDES) $(PRINTF) -o $@

$(ASM_OBJS_DIR)%.o: $(ASM_DIR)%.c
	@mkdir -p $(ASM_OBJS_DIR)
	gcc -c $< $(INCLUDES) -o $@

################ Printf ################

$(PRINTF):
	make -C $(PRINTF_DIR)

################ others ################

clean:
	make clean -C $(PRINTF_DIR)
	rm -rf objs/

fclean: clean
	make fclean -C $(PRINTF_DIR)
	rm -f $(COR_NAME)
	rm -f $(ASM_NAME)

re: fclean all

.PHONY: clean fclean re
