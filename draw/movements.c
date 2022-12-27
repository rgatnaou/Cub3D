/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:48:51 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/27 10:45:03 by rgatnaou         ###   ########.fr       */
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
	int dist;

	dist = 0;
	data->player.rotation_angle += data->move.rotation * M_PI / 180.0;

	if (data->move.ws_move)
	{	
		int step = data->move.ws_move  * SPEED;
		double x = data->player.cord.x + cos(data->player.rotation_angle) * step;
		double y = data->player.cord.y  + sin(data->player.rotation_angle) * step;
		if (!check_if_wall(data, x , y + dist))
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
		if (limit_angle(data->player.rotation_angle) > M_PI / 2 && limit_angle(data->player.rotation_angle) < 3 * M_PI / 2)
			dist = 10 * data->move.ad_move;
		else
			dist = -10 * data->move.ad_move;
		if (!check_if_wall(data, x, y))
		{
			data->player.cord.x = x;
			data->player.cord.y = y;
		}
	}

}
