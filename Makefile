# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrummuka <jrummuka@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 23:59:55 by qnguyen           #+#    #+#              #
#    Updated: 2022/12/05 18:51:48 by vkinnune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COR_NAME = corewar
COR_DIR = srcs/corewar/
# add new .c files here
COR_FILE = main player_handler error error2 utilities parse process process_util \
			 corewar player_sort instruction instruction2 instruction3 instruc_util \
			 init print verbose verbose2 verbose3
COR_OBJS_DIR = objs/corewar/
COR_OBJS = $(addprefix $(COR_OBJS_DIR), $(addsuffix .o, $(COR_FILE)))

ASM_NAME = asm
ASM_DIR = srcs/asm/
# add new .c files here
ASM_FILE = main validate parser parser2 parser3 parser4 parser5 parser6 checks error write instruction_handler utilities\
			label label_utils arg_handler
ASM_OBJS_DIR = objs/asm/
ASM_OBJS = $(addprefix $(ASM_OBJS_DIR), $(addsuffix .o, $(ASM_FILE)))

SHARE_DIR = srcs/shared/
# add new .c files here
SHARED_FILE = op shared_util
SHARED_OBJS_DIR = objs/shared/
SHARED_OBJS = $(addprefix $(SHARED_OBJS_DIR), $(addsuffix .o, $(SHARED_FILE)))

PRINTF = libraries/libftprintf.a
PRINTF_DIR = srcs/printf/

FLAG = -Wall -Werror -Wextra -g
INCLUDES = -I includes

all: $(COR_NAME) $(ASM_NAME)

################ COREWAR ################

$(COR_NAME): $(SHARED_OBJS) $(COR_OBJS)
	gcc $(FLAG) $(COR_OBJS) $(SHARED_OBJS) $(INCLUDES) $(PRINTF) -o $@

$(COR_OBJS_DIR)%.o: $(COR_DIR)%.c includes/corewar.h
	@mkdir -p $(COR_OBJS_DIR)
	gcc $(FLAG) -c $< $(INCLUDES) -o $@

################ ASM ################

$(ASM_NAME): $(SHARED_OBJS) $(ASM_OBJS)
	gcc $(FLAG) $(ASM_OBJS) $(SHARED_OBJS) $(INCLUDES) $(PRINTF) -o $@

$(ASM_OBJS_DIR)%.o: $(ASM_DIR)%.c includes/asm.h
	@mkdir -p $(ASM_OBJS_DIR)
	gcc $(FLAG) -c $< $(INCLUDES) -o $@

################ Shared ################

$(SHARED_OBJS_DIR)%.o: $(SHARE_DIR)%.c $(PRINTF)
	@mkdir -p $(SHARED_OBJS_DIR)
	gcc $(FLAG) -c $< $(INCLUDES) -o $@

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
