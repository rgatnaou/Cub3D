/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:30:16 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/08/24 20:11:50 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include"../libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <stdio.h>

# define KEY_W 13
# define KEY_D 2
# define KEY_A 0
# define KEY_S 1
# define KEY_ESC 53

typedef struct s_data {
	void	*mlx;
	void	*win;
	char	**map;
	void	*tex[4];
	int		color[2];
	int		p[2];
	// void	*mlx_player;
	// void	*mlx_exit;
	// void	*mlx_space;
}	t_data;
int draw(t_data *m);

#endif