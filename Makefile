# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/19 18:37:56 by rgatnaou          #+#    #+#              #
#    Updated: 2022/12/29 15:50:20 by rgatnaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = CUB3D

LIBFT = libft/libft.a

HEADER = includes/cub3D.h

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC =  main.c \
	parsing/parse.c \
	parsing/create_data.c \
	parsing/create_data_utils.c \
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

%.o : %.c $(HEADER)
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