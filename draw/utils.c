/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:19:52 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/27 18:36:28 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	if ((x < WIDTH && x >= 0) && (y < HEIGHT && y >= 0))
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
}

int	destroy_win(t_data *data)
{
	mlx_destroy_image(data->mlx.init, data->mlx.image.img);
	mlx_destroy_window(data->mlx.init, data->mlx.win);
	free_data(data);
	exit(0);
}

void	ws_move(t_data *data, int step, double dist)
{
	double	x;
	double	y;

	step = data->move.ws_move * SPEED;
	x = data->player.cord.x + cos(data->player.rotation_angle) * step;
	y = data->player.cord.y + sin(data->player.rotation_angle) * step;
	if (!check_if_wall(data, x, y + dist))
	{
		data->player.cord.x = x;
		data->player.cord.y = y;
	}
}

void	ad_move(t_data *data, int step, double dist)
{
	double	x;
	double	y;

	step = data->move.ad_move * SPEED;
	x = data->player.cord.x + cos(data->player.rotation_angle + (M_PI / 2))
		* step;
	y = data->player.cord.y + sin(data->player.rotation_angle + (M_PI / 2))
		* step;
	if (limit_angle(data->player.rotation_angle) > M_PI / 2
		&& limit_angle(data->player.rotation_angle) < 3 * M_PI / 2)
		dist = 10 * data->move.ad_move;
	else
		dist = -10 * data->move.ad_move;
	if (!check_if_wall(data, x, y))
	{
		data->player.cord.x = x;
		data->player.cord.y = y;
	}
}
