# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmicheal <bmicheal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/24 11:50:04 by bmicheal          #+#    #+#              #
#    Updated: 2021/03/12 14:46:28 by bmicheal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all re fclean clean

NAME = minishell

SRC = $(addprefix srcs/,\
    signal.c\
	error_list.c\
	shell.c\
	lexer_utils.c\
	token_util.c\
	cmd_util.c\
	parse_cmd.c\
	parse_token.c\
	parse_util.c\
	parse_util2.c\
	execute.c\
	exec_util.c\
	exec_util2.c\
	exec_util3.c\
	util.c\
	env_util.c\
	builtins/echo.c\
	builtins/cd.c\
	builtins/export.c\
	builtins/export_utils.c\
	builtins/pwd.c\
	builtins/unset.c\
	builtins/env.c\
	builtins/ft_exit.c\
	builtins/execute.c)

SRCO = $(SRC:.c=.o)

CC = gcc

LIBFT = $(LIBFTDIR)libft.a

LIBFTDIR = libft/

INCLUDES = -Iincludes/ -Ilibft/

CFLAGS = -Wall -Werror -Wextra -Ilibft/ $(INCLUDES) -g

all: $(NAME)

$(NAME): $(SRCO) $(LIBFT) includes/minishell.h
	$(CC) $(SRCO) $(INCLUDES) -L$(LIBFTDIR) -lft -o $(NAME) -g

$(LIBFT):
	make -C $(LIBFTDIR)

clean:
	rm -f $(SRCO)
	make clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFTDIR)

re: fclean all