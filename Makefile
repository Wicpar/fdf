# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/19 14:09:58 by apachkof          #+#    #+#              #
#    Updated: 2016/01/06 13:05:53 by fnieto           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fdf

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

SRC=main.c ft_cos.c ft_sin.c ft_sqrt.c matrix.c vector.c vector_complex.c

LIB= -framework OpenGL -framework AppKit libft/libft.a minilibx_macos/libmlx.a

INCL=-I libft/includes/ -I minilibx_macos/

OBJ=$(SRC:.c=.o)

$(NAME): fdf.h
		make -C libft/
		make -C minilibx_macos/
		$(CC) $(CFLAGS) $(INCL) -c $(SRC)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INCL) $(LIB)


all: $(NAME)

clean:
		make -C libft/ clean
		$(RM) $(OBJ)

fclean: clean
		make -C libft/ fclean
		$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean
