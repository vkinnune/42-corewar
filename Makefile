# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 23:59:55 by qnguyen           #+#    #+#              #
#    Updated: 2022/10/27 14:04:54 by vkinnune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COR_NAME = corewar
COR_DIR = srcs/corewar/
# add new .c files here
COR_FILE = main
COR_OBJS_DIR = objs/corewar/
COR_OBJS = $(addprefix $(COR_OBJS_DIR), $(addsuffix .o, $(COR_FILE)))

ASM_NAME = asm
ASM_DIR = srcs/asm/src/
# add new .c files here
ASM_FILE = main
ASM_OBJS_DIR = objs/asm/
ASM_OBJS = $(addprefix $(ASM_OBJS_DIR), $(addsuffix .o, $(ASM_FILE)))

PRINTF = libraries/libftprintf.a
PRINTF_DIR = srcs/printf/

FLAG = -Wall -Werror -Wextra
INCLUDES = -I includes
ASM_INCLUDES = -I srcs/asm/includes/

all: $(COR_NAME) $(ASM_NAME)

################ COREWAR ################

$(COR_NAME): $(COR_OBJS) $(PRINTF)
	gcc $< $(INCLUDES) $(PRINTF) -o $@

$(COR_OBJS_DIR)%.o: $(COR_DIR)%.c
	mkdir -p $(COR_OBJS_DIR)
	gcc -c $< $(INCLUDES) -o $@

################ ASM ################

$(ASM_NAME): $(ASM_OBJS) $(PRINTF)
	gcc $< $(INCLUDES) $(ASM_INCLUDES) $(PRINTF) -o $@

$(ASM_OBJS_DIR)%.o: $(ASM_DIR)%.c
	mkdir -p $(ASM_OBJS_DIR)
	gcc -c $< $(INCLUDES) $(ASM_INCLUDES) -o $@

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