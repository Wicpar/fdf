# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/19 14:09:58 by apachkof          #+#    #+#              #
#    Updated: 2016/01/11 18:26:55 by fnieto           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fdf

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

SRC=main.c error.c get_next_line.c

LIB= -framework OpenGL -framework AppKit libft/libft.a minilibx_macos/libmlx.a fred_gl/fred_gl.a

INCL=-I libft/includes/ -I minilibx_macos/ -I fred_gl/

OBJ=$(SRC:.c=.o)

$(NAME): fdf.h
		make -C libft/
		make -C fred_gl/
		make -C minilibx_macos/
		$(CC) $(CFLAGS) $(INCL) -c $(SRC)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INCL) $(LIB)


all: $(NAME)

clean:
		make -C libft/ clean
		make -C fred_gl/ clean
		$(RM) $(OBJ)

fclean: clean
		make -C libft/ fclean
		make -C fred_gl/ fclean
		$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean
