/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:02:03 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/31 12:50:14 by rgatnaou         ###   ########.fr       */
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
	mlx_destroy_image(data->mlx.init, data->texture.no.img_ptr);
	mlx_destroy_image(data->mlx.init, data->texture.so.img_ptr);
	mlx_destroy_image(data->mlx.init, data->texture.ea.img_ptr);
	mlx_destroy_image(data->mlx.init, data->texture.we.img_ptr);
	mlx_destroy_window(data->mlx.init, data->mlx.win);
	free_data(data);
	exit(0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->move.ws_move = 0;
	else if (keycode == KEY_S)
		data->move.ws_move = 0;
	else if (keycode == KEY_D)
		data->move.ad_move = 0;
	else if (keycode == KEY_A)
		data->move.ad_move = 0;
	else if (keycode == KEY_ARROW_RIGHT)
		data->move.rotation = 0;
	else if (keycode == KEY_ARROW_LEFT)
		data->move.rotation = 0;
	return (0);
}

int	key_pressed(int keycode, t_data *data)
{
	if (keycode == KEY_D)
		data->move.ad_move = 1;
	else if (keycode == KEY_A)
		data->move.ad_move = -1;
	else if (keycode == KEY_S)
		data->move.ws_move = -1;
	else if (keycode == KEY_W)
		data->move.ws_move = 1;
	else if (keycode == KEY_ARROW_RIGHT)
		data->move.rotation = 1;
	else if (keycode == KEY_ARROW_LEFT)
		data->move.rotation = -1;
	else if (keycode == KEY_ESC)
		destroy_win(data);
	return (0);
}
