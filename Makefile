# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/19 18:37:56 by rgatnaou          #+#    #+#              #
#    Updated: 2022/08/21 10:58:19 by rgatnaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = CUB3D

LIBFT = libft/libft.a

HEADER = ./cub3d.h ./parce_map/parce.h
		 

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC =  main.c parce/parce.c parce/utils.c parce/texture.c parce/map.c

OBJECTS = $(SRC:.c=.o)

%.o : %.c $(HEADER) $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@ 

all: MAKELIBFT $(NAME)

MAKELIBFT: 
	make -C libft

$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $^ $(LIBFT) -o $(NAME)

clean:
	make fclean -C libft
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all