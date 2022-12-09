/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:48:51 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/09 19:12:36 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	key_press_d(t_data *data)
{
	double	angle;
	int		x_player;
	int		y_player;

	angle = data->player.rotation_angle + (M_PI / 2);
	x_player = roundf(data->player.cord.x + (cos(angle) * SPEED));
	y_player = roundf(data->player.cord.y + (sin(angle) * SPEED));
	if (!check_if_wall(data, x_player, y_player))
	{
		data->player.cord.x = x_player;
		data->player.cord.y = y_player;
	}
	draw_2d_map(data);
}

void	key_press_a(t_data *data)
{
	double	angle;
	int		x_player;
	int		y_player;

	angle = data->player.rotation_angle - (M_PI / 2);
	x_player = roundf(data->player.cord.x + (cos(angle) * SPEED));
	y_player = roundf(data->player.cord.y + (sin(angle) * SPEED));
	if (!check_if_wall(data, x_player, y_player))
	{
		data->player.cord.x = x_player;
		data->player.cord.y = y_player;
	}
	draw_2d_map(data);
}

void	key_press_s(t_data *data)
{
	int	x_player;
	int	y_player;

	x_player = roundf(data->player.cord.x - cos(data->player.rotation_angle)
			* SPEED);
	y_player = roundf(data->player.cord.y - sin(data->player.rotation_angle)
			* SPEED);
	if (!check_if_wall(data, x_player, y_player))
	{
		data->player.cord.x = x_player;
		data->player.cord.y = y_player;
	}
	draw_2d_map(data);
}

void	key_press_w(t_data *data)
{
	int	x_player;
	int	y_player;

	x_player = roundf(data->player.cord.x + cos(data->player.rotation_angle)
			* SPEED);
	y_player = roundf(data->player.cord.y + sin(data->player.rotation_angle)
			* SPEED);
	if (!check_if_wall(data, x_player, y_player))
	{
		data->player.cord.x = x_player;
		data->player.cord.y = y_player;
	}
	draw_2d_map(data);
}

int	move_player(int keycode, t_parse *parsing)
{
	if (keycode == KEY_D)
		key_press_d(parsing->data);
	if (keycode == KEY_A)
		key_press_a(parsing->data);
	if (keycode == KEY_S)
		key_press_s(parsing->data);
	if (keycode == KEY_W)
		key_press_w(parsing->data);
	if (keycode == KEY_ARROW_RIGHT)
	{
		parsing->data->player.rotation_angle += SPEED * M_PI / 180.0;
		draw_2d_map(parsing->data);
	}
	if (keycode == KEY_ARROW_LEFT)
	{
		parsing->data->player.rotation_angle -= SPEED * M_PI / 180.0;
		draw_2d_map(parsing->data);
	}
	if (keycode == KEY_ESC)
		destroy_win(parsing);
	return (0);
}
