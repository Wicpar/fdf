# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/19 14:09:58 by apachkof          #+#    #+#              #
#    Updated: 2016/02/03 17:54:24 by fnieto           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fdf

CC=gcc

CFLAGS=-Wall -Wextra -Werror -O3

RM=rm -f

SRC=main.c error.c get_next_line.c map.c ft_str_split_lst.c shaders1.c t_map.c

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
