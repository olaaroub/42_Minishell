# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 03:42:07 by hatalhao          #+#    #+#              #
#    Updated: 2024/11/26 08:03:22 by hatalhao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
# CFLAGS += -fsanitize=address -g3
MAKEFLAGS := -j --no-print-directory

# ITALICBOLD
GREEN = \033[0;32m
RESET = \033[0m
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
	@echo "✅ $(GREEN)$(NAME)$(RESET)"


$(LIB):
	@make -C libft
	@echo "✅ $(GREEN)libft$(RESET)"

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
