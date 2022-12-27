# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/19 18:37:56 by rgatnaou          #+#    #+#              #
#    Updated: 2022/12/27 18:35:49 by ykhadiri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = CUB3D

LIBFT = libft/libft.a

HEADER = includes/cub3D.h

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Ofast

SRC =  main.c \
	parsing/parse.c \
	parsing/create_data.c \
	parsing/ft_free.c \
	parsing/utils_map.c \
	parsing/utils.c \
	parsing/texture.c \
	parsing/map.c \
	draw/draw.c \
	draw/draw_shap.c \
	draw/movements.c \
	draw/key_events.c \
	draw/utils.c \
	raycasting/raycasting.c \
	raycasting/raycasting_utils1.c \
	raycasting/raycasting_utils2.c \
	projection/projection.c

OBJECTS = $(SRC:.c=.o)

%.o : %.c $(HEADER) $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@ 

all: MAKELIBFT $(NAME)

MAKELIBFT: 
	make -C libft

$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $^ $(LIBFT) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	make fclean -C libft
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all