/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:48:51 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/23 18:36:40 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	key_press_d(t_data *data)
{
	double	angle;
	double		x_player;
	double		y_player;

	angle = data->player.rotation_angle + (M_PI / 2);
	x_player = (data->player.cord.x + (cos(angle) * SPEED));
	y_player = (data->player.cord.y + (sin(angle) * SPEED));
	if (!check_if_wall(data, x_player, y_player))
	{
		data->player.cord.x = x_player;
		data->player.cord.y = y_player;
	}
}

void	key_press_a(t_data *data)
{
	double	angle;
	double		x_player;
	double		y_player;

	angle = data->player.rotation_angle - (M_PI / 2);
	x_player = (data->player.cord.x + (cos(angle) * SPEED));
	y_player = (data->player.cord.y + (sin(angle) * SPEED));
	if (!check_if_wall(data, x_player, y_player))
	{
		data->player.cord.x = x_player;
		data->player.cord.y = y_player;
	}
}

void	key_press_s(t_data *data)
{
	double	x_player;
	double	y_player;


	x_player = (data->player.cord.x - cos(data->player.rotation_angle)
			* SPEED);
	y_player = (data->player.cord.y - sin(data->player.rotation_angle)
			* SPEED);
	
	if (!check_if_wall(data, x_player, y_player))
	{
		data->player.cord.x = x_player;
		data->player.cord.y = y_player;
	}
}

void	key_press_w(t_data *data)
{
	double	x_player;
	double	y_player;

	x_player = (data->player.cord.x + cos(data->player.rotation_angle)
			* SPEED);
	y_player = (data->player.cord.y + sin(data->player.rotation_angle)
			* SPEED);
	if (!check_if_wall(data, x_player, y_player))
	{
		data->player.cord.x = x_player;
		data->player.cord.y = y_player;
	}
}

void	move_player(t_data *data)
{
	data->player.rotation_angle += data->move.rotation * 3 * M_PI / 180.0;

	if (data->move.ws_move)
	{	
		int step = data->move.ws_move  * SPEED;
		double x = data->player.cord.x + cos(data->player.rotation_angle) * step;
		double y = data->player.cord.y  + sin(data->player.rotation_angle) * step;
		if (!check_if_wall(data, x, y))
		{
			data->player.cord.x = x;
			data->player.cord.y = y;
		}
	}
	if (data->move.ad_move)
	{	
		int step = data->move.ad_move  * SPEED;
		double x = data->player.cord.x + cos(data->player.rotation_angle + (M_PI /2)) * step;
		double y = data->player.cord.y  + sin(data->player.rotation_angle + (M_PI /2)) * step;
		if (!check_if_wall(data, x, y))
		{
			data->player.cord.x = x;
			data->player.cord.y = y;
		}
	}
	// if (KEY_S == data->move.ws_move)
	// 	key_press_s(data);
	// if (KEY_D == data->move.ad_move)
	// 	key_press_d(data);
	// if (KEY_W == data->move.ws_move)
	// 	key_press_w(data);
	// if (KEY_A == data->move.ad_move)
	// 	key_press_a(data);
	// if (KEY_ARROW_RIGHT == data->move.rotation)
	// 	data->player.rotation_angle += M_PI / 180.0;
	// if (KEY_ARROW_LEFT == data->move.rotation)
	// 	data->player.rotation_angle -= M_PI / 180.0;
}
