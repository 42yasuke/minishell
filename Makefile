# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jose <jose@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/28 20:06:58 by jose              #+#    #+#              #
#    Updated: 2023/06/01 02:04:34 by jose             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

CFLAGS_OBJ = -Wall -Wextra -Werror -c -g

RM = rm -f

C_FILES =	main.c \
			error.c \
			builtin.c \
			builtin2.c \
			builtin3.c \
			builtin4.c \
			utils.c \
			utils2.c \
			utils3.c \
			exec.c \
			parse.c \
			init.c \
			path.c \
			free.c \
			node_env.c \
			node_env2.c \
			sdquote.c \
			sdquote2.c \
			sdquote3.c \
			export.c \
			ft_illtoa.c \
			redir.c \
			echo.c \
			ft_pipe.c

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