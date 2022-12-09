/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:43:43 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/09 19:14:10 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	circle(t_mlx *mlx, int x, int y, int r, int color)
{
	double	i;
	double	angle;
	double	x1;
	double	y1;

	while (r)
	{
		i = 0;
		while (i < 360)
		{
			angle = i;
			x1 = r * cos(angle * M_PI / 180);
			y1 = r * sin(angle * M_PI / 180);
			my_mlx_pixel_put(&mlx->image, roundf(x + x1), roundf(y + y1),
				color);
			i += 0.1;
		}
		r--;
	}
}

void	square(t_mlx *mlx, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i <= SIZE_CUB)
	{
		j = 0;
		while (j <= SIZE_CUB && ((x + j) < WIDTH && (y + i) < HEIGHT))
		{
			if ((j > SIZE_CUB - 1) || (i > SIZE_CUB - 1) || i < 1 || j < 1)
				my_mlx_pixel_put(&mlx->image, (x + j), (y + i), 0x00ffff);
			else
				my_mlx_pixel_put(&mlx->image, (x + j), (y + i), color);
			j++;
		}
		i++;
	}
}

void	line(t_data *data, int x_end, int y_end, int color)
{
	float	dis_x;
	float	dis_y;
	float	x;
	float	y;
	int		step;

	dis_x = x_end - data->player.cord.x;
	dis_y = y_end - data->player.cord.y;
	if (fabs(dis_x) >= fabs(dis_y))
		step = fabs(dis_x);
	else
		step = fabs(dis_y);
	x = data->player.cord.x;
	y = data->player.cord.y;
	dis_x /= step;
	dis_y /= step;
	while (step)
	{
		my_mlx_pixel_put(&data->mlx->image, roundf(x), roundf(y), color);
		x += dis_x;
		y += dis_y;
		step--;
	}
}

void	draw_player(t_data *data)
{
	circle(data->mlx, data->player.cord.x, data->player.cord.y, 2, RED);
	draw_rays(data);
}
