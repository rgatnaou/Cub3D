/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:30:16 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/01 19:05:33 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# define WIDTH 1024
# define HEIGHT 800

# include "../libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <stdio.h>

# define WHITE 0Xffffff
# define BLUE 0X0000ff


# define KEY_W 13
# define KEY_D 2
# define KEY_A 0
# define KEY_S 1
# define KEY_ESC 53
# define PI 3.14159265359

typedef struct	s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct s_mlx {
	void	*mlx;
	void	*win;
	char	**map;
	void	*tex[4];
	int		color[2];
	float	p[3];
	// void	*mlx_player;
	// void	*mlx_exit;
	// void	*mlx_space;
	t_image img;
}	t_mlx;


int draw(t_mlx *mlx);

#endif