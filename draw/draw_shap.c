/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:43:43 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/31 16:08:18 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	circle(t_mlx *mlx, t_cord *coord, int r, int color)
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
			my_mlx_pixel_put(&mlx->image, roundf(coord->x + x1), roundf(coord->y
					+ y1), color);
			i += 0.1;
		}
		r--;
	}
}

void	square(t_mlx *mlx, t_cord *cord, int color)
{
	int		i;
	int		j;
	t_cord	draw;

	i = 0;
	while (i < MINIMAP)
	{
		j = 0;
		while (j < MINIMAP)
		{
			draw.x = cord->x + j;
			draw.y = cord->y + i;
			if (i == 0 || j == 0)
				my_mlx_pixel_put(&mlx->image, draw.x, draw.y, GRAY);
			else
				my_mlx_pixel_put(&mlx->image, draw.x, draw.y, color);
			j++;
		}
		i++;
	}
}

void	line(t_data *data, t_cord *start, t_cord *end)
{
	double	dis_x;
	double	dis_y;
	double	x;
	double	y;
	int		step;

	x = start->x;
	y = start->y;
	dis_x = end->x - x;
	dis_y = end->y - y;
	step = fmax(fabs(dis_x), fabs(dis_y));
	dis_x /= step;
	dis_y /= step;
	while (step)
	{
		my_mlx_pixel_put(&data->mlx.image, x, y, RED);
		x += dis_x;
		y += dis_y;
		step--;
	}
}

void	draw_player(t_data *data, t_cord *start)
{
	int		i;
	t_cord	end;

	i = 0;
	circle(&data->mlx, start, 2, RED);
	end.x = start->x + (cos(data->player.rotation_angle) * 10);
	end.y = start->y + (sin(data->player.rotation_angle) * 10);
	line(data, start, &end);
}
