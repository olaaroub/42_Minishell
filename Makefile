# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/08 10:57:09 by olaaroub          #+#    #+#              #
#    Updated: 2024/11/09 21:47:43 by hatalhao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -fsanitize=address -g3
MAKEFLAGS := -j

SRC = src_parsing/main.c src_parsing/get_env.c src_parsing/trash.c src_parsing/split_mgem7a.c
SRC += src_parsing/tokenizing.c src_parsing/tokens_list.c src_parsing/check_line.c src_parsing/utils-v1.c
SRC += src_parsing/syntax_error.c src_parsing/expand_v2.c src_parsing/split_after_expand.c
SRC += src_parsing/fill_command_list.c src_parsing/command_list.c
SRC += $(wildcard builtins/*.c)
SRC += $(wildcard src_execution/*.c)

#=== PRINTF_FD ===#
SRC += $(wildcard libft/ft_printf/*.c)

OBJ = $(SRC:.c=.o)

NAME = minishell_1
LIB = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIB)  -lreadline -o $(NAME)
	make clean

$(LIB):
	make -C libft

clean:
	@rm -rf $(OBJ)
	@make clean -C libft

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIB)

re:
	make fclean
	make all

.PHONY: all fclean clean re bonus
.SECONDARY: $(OBJ)
