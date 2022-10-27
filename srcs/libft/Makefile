# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/29 19:02:23 by qnguyen           #+#    #+#              #
#    Updated: 2022/10/27 13:44:41 by vkinnune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OUTPUT_DIR = ../../libraries
NAME = $(OUTPUT_DIR)/libft.a
SRCS = ft_abs ft_arrdel ft_atoi ft_bzero ft_calloc ft_countwords ft_d2base ft_d2base_fd\
ft_diglen ft_udiglen ft_greaternum ft_isspace\
ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_itoa ft_isprint ft_linkdel \
ft_lstadd_back ft_lstadd ft_lstdel ft_lstdelone ft_lstiter ft_lstlast \
ft_lstmap ft_lstnew ft_lststrsplit ft_memalloc ft_memccpy ft_memchr ft_memcmp \
ft_memcpy ft_memdel ft_memmove ft_memset ft_pow ft_putchar_fd ft_putchar \
ft_putendl_fd ft_putendl ft_putfloat ft_putfloat_fd\
ft_putnbr_fd ft_putnbr ft_putstr ft_putstr_fd ft_smallernum ft_sqrt\
ft_strcat ft_strchr ft_strclr ft_strcmp ft_strcpy ft_strdel ft_strdup \
ft_strequ ft_striter ft_striteri ft_strjoin ft_strlcat ft_strlen ft_strmap \
ft_strmapi ft_strncat ft_strncmp ft_strncpy ft_strnequ ft_strnew ft_strnstr \
ft_strrchr ft_strsplit ft_strstr ft_strsub ft_strtrim ft_swap ft_tolower ft_toupper ft_out
FLAGS = -Wall -Wextra -Werror
OBJS_DIR = ../../objs/libft/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS)))
INCLUDES = ../../includes/

all: $(NAME)

$(NAME): $(OBJS) $(OUTPUT_DIR)
	ar -rcs $(NAME) $(OBJS)

$(OBJS_DIR)%.o: %.c $(INCLUDES)libft.h $(OBJS_DIR)
	gcc -c $(FLAGS) -I$(INCLUDES) $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

clean:
	@/bin/rm -rf ../objs/
	@/bin/rm -f $(OBJS)

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -rf $(OUTPUT_DIR)

re: fclean all

.PHONY: clean fclean all re
