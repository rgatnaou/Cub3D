/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:48:51 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/16 18:15:12 by ykhadiri         ###   ########.fr       */
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
}

void	move_player(t_data *data)
{
	if (KEY_S == data->move.ws_move)
		key_press_s(data);
	if (KEY_D == data->move.ad_move)
		key_press_d(data);
	if (KEY_W == data->move.ws_move)
		key_press_w(data);
	if (KEY_A == data->move.ad_move)
		key_press_a(data);
	if (KEY_ARROW_RIGHT == data->move.rotation)
	// SPEED == SPEED / 2
		data->player.rotation_angle += M_PI / 180.0;
	if (KEY_ARROW_LEFT == data->move.rotation)
		data->player.rotation_angle -= M_PI / 180.0;
}
