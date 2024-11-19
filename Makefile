# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 03:42:07 by hatalhao          #+#    #+#              #
#    Updated: 2024/11/19 04:02:08 by hatalhao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -fsanitize=address -g3
MAKEFLAGS := -j --no-print-directory

# ITALICBOLD
GREEN = \033[0;32m
# SRC = src_parsing/main.c src_parsing/get_env.c src_parsing/trash.c src_parsing/split_mgem7a.c
# SRC += src_parsing/tokenizing.c src_parsing/tokens_list.c src_parsing/check_line.c src_parsing/utils-v1.c
# SRC += src_parsing/syntax_error.c src_parsing/expand_v2.c src_parsing/split_after_expand.c
# SRC += src_parsing/fill_command_list.c src_parsing/command_list.c
SRC += $(wildcard builtins/*.c)
SRC += $(wildcard src_parsing/*.c)
SRC += $(wildcard src_execution/*.c)

#=== PRINTF_FD ===#
SRC += $(wildcard libft/ft_printf/*.c)

OBJ = $(SRC:.c=.o)

NAME = minishell
LIB = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIB)  -lreadline -o $(NAME)
	make clean
# add check emoji
	@echo "✅ $(GREEN)$(NAME)"
	

$(LIB):
	@make -C libft
	@echo "✅ $(GREEN)libft"
	
clean:
	@rm -rf $(OBJ)
	@make clean -C libft

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIB)

re:
	@make fclean
	@make all

.PHONY: all fclean clean re bonus
.SECONDARY: $(OBJ)
.SILENT: $(OBJ) $(NAME)