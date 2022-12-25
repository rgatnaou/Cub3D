/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:43:43 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/25 08:46:37 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// void	circle(t_mlx *mlx, t_cord coord, int r, int color)
// {
// 	double	i;
// 	double	angle;
// 	double	x1;
// 	double	y1;

// 	coord.x *= MINIMAP_FACTOR;
// 	coord.y *= MINIMAP_FACTOR;
// 	r *= MINIMAP_FACTOR;
// 	while (r)
// 	{
// 		i = 0;
// 		while (i < 360)
// 		{
// 			angle = i;
// 			x1 = r * cos(angle * M_PI / 180);
// 			y1 = r * sin(angle * M_PI / 180);
// 			my_mlx_pixel_put(&mlx->image, roundf(coord.x + x1), roundf(coord.y
// 						+ y1), color);
// 			i += 0.1;
// 		}
// 		r--;
// 	}
// }

// void	circle(t_mlx *mlx, t_cord *coord, int r, int color)
// {
// 	double	i;
// 	double	angle;
// 	double	x1;
// 	double	y1;

// 	coord->x *= MINIMAP_FACTOR;
// 	coord->y *= MINIMAP_FACTOR;
// 	r *= MINIMAP_FACTOR;
// 	while (r)
// 	{
// 		i = 0;
// 		while (i < 360)
// 		{
// 			angle = i;
// 			x1 = r * cos(angle * M_PI / 180);
// 			y1 = r * sin(angle * M_PI / 180);
// 			my_mlx_pixel_put(&mlx->image, roundf(coord->x + x1), roundf(coord->y
// 						+ y1), color);
// 			i += 0.1;
// 		}
// 		r--;
// 	}
// }

void	square(t_mlx *mlx, int x, int y, int color)
{
	int	i;
	int	j;
	int	size_cube_minimap;

	size_cube_minimap = SIZE_CUB * MINIMAP_FACTOR;
	x *= MINIMAP_FACTOR;
	y *= MINIMAP_FACTOR;
	i = 0;
	while (i <= size_cube_minimap)
	{
		j = 0;
		while (j <= size_cube_minimap && ((x + j) < WIDTH && (y + i) < HEIGHT))
		{
			if (i == 0 || j == 0 )
				my_mlx_pixel_put(&mlx->image, (x + j), (y + i), 0x808080);
			else
				my_mlx_pixel_put(&mlx->image, (x + j), (y + i), color);
			j++;
		}
		i++;
	}
}

void	line(t_data *data, double x_end, double y_end, int color)
{
	double	dis_x;
	double	dis_y;
	double	x;
	double	y;
	double		step;

	x_end *= MINIMAP_FACTOR;
	x = data->player.cord.x * MINIMAP_FACTOR;
	y = data->player.cord.y * MINIMAP_FACTOR;
	y_end *= MINIMAP_FACTOR;
	dis_x = x_end - x;
	dis_y = y_end - y;
	step = fmax(fabs(dis_x), fabs(dis_y));
	dis_x /= step;
	dis_y /= step;
	while (step >= 0)
	{
		my_mlx_pixel_put(&data->mlx->image, roundf(x), roundf(y), color);
		x += dis_x;
		y += dis_y;
		step--;
	}
}

// void	draw_player(t_data *data)
// {
// 	int		i;
// 	double	ray_angle;

// 	i = 0;
// 	ray_angle = data->player.rotation_angle - (FOV / 2);
// 	circle(data->mlx, data->player.cord, 5, RED);
// 	line(data, data->player.cord.x + (cos(data->player.rotation_angle) * 50),
// 			data->player.cord.y + (sin(data->player.rotation_angle) * 50), RED);
// }

// void	line1(t_data *data, double x_end, double y_end,t_cord *start, int color)
// {
// 	double	dis_x;
// 	double	dis_y;
// 	double	x;
// 	double	y;
// 	int		step;

// 	x = start->x;
// 	y = start->y;
// 	dis_x = x_end - x;
// 	dis_y = y_end - y;
// 	step = fmax(fabs(dis_x), fabs(dis_y));
// 	dis_x /= step;
// 	dis_y /= step;
// 	while (step)
// 	{
// 		my_mlx_pixel_put(&data->mlx->image, x, y, color);
// 		x += dis_x;
// 		y += dis_y;
// 		step--;
// 	}
// }

// void	draw_player(t_data *data ,t_cord *start)
// {
// 	int		i;
// 	double	ray_angle;

// 	i = 0;
// 	ray_angle = data->player.rotation_angle - (FOV / 2);
// 	circle(data->mlx, start, 5, RED);
// 	line1(data, start->x+ (cos(data->player.rotation_angle) * 10),
// 			start->y + (sin(data->player.rotation_angle) * 10), start,RED);
// }