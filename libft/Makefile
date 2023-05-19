# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jose <jose@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 11:53:36 by jralph            #+#    #+#              #
#    Updated: 2023/01/28 01:47:23 by jose             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC =	ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		get_next_line.c \
		ft_printf.c \
		ft_putchar.c \
		ft_putstr.c \
		ft_goodc.c \
		ft_putptr.c \
		ft_putnbr.c \
		ft_putnbru.c \
		ft_puthexa_min.c \
		ft_puthexa_maj.c

BONUS =	ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c

OBJ = $(SRC:.c=.o)

OBJ_B = $(BONUS:.c=.o)

AR = ar

AFLAGS = -crs

NAME = libft.a

RM = rm -f


all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
$(NAME) : $(OBJ)
	$(AR) $(AFLAGS) $(NAME) $^

bonus : $(OBJ) $(OBJ_B)
	$(AR) $(AFLAGS) $(NAME) $(OBJ) $(OBJ_B)
	mv $(NAME) ../

clean :
	$(RM) $(OBJ) $(OBJ_B)

fclean : clean
	$(RM) $(NAME)
	
re : fclean all

prog : main.c bonus 
	$(CC) $(CFLAGS) $<  -L. -lft -lbsd -o $@

fprog : fclean
	$(RM) prog
