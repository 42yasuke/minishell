# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jose <jose@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/28 20:06:58 by jose              #+#    #+#              #
#    Updated: 2023/09/25 11:51:26 by jose             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

CFLAGS_OBJ = -Wall -Wextra -Werror -c -g

RM = rm -f

C_FILES =	main.c \
			error.c \
			builtin.c \
			ft_cd.c ft_pwd.c ft_env.c ft_unset.c ft_echo.c \
			ft_export.c ft_export_utils.c \
			ft_export_remove_space.c \
			ft_update_env.c \
			ft_exit.c ft_exit_utils.c \
			utils.c \
			exec.c \
			parse.c \
			init.c init_ginf.c \
			path.c \
			free.c \
			node_env.c \
			sdquote.c \
			sdquote2.c \
			sdquote3.c \
			ft_illtoa.c \
			redir.c redir_utils.c \
			here_doc.c \
			ft_pipe.c \
			ft_verif_line.c ft_verif_cmd.c \
			replace.c \
			chr_var_denv.c

SRC = $(addprefix src/, $(C_FILES))

OBJ = $(SRC:.c=.o)

INC = -I includes/

LIB = -L. -lft

NAME = minishell

all : $(NAME)

libft.a :
			make bonus -C libft

%.o : %.c
			$(CC) $(CFLAGS_OBJ) $< -o $@ $(INC)

$(NAME) : $(OBJ) libft.a
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIB) -lreadline

clean :
		make clean -C libft
		$(RM) src/*.o

fclean : clean
		$(RM) $(NAME) libft.a

re : fclean all

.PHONY : all fclean clean re

prog : all clean
		clear