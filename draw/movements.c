/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:48:51 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/30 11:01:23 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	ws_move(t_data *data)
{
	double	x;
	double	y;
	int		step;

	step = data->move.ws_move * SPEED;
	x = data->player.cord.x + cos(data->player.rotation_angle) * step;
	y = data->player.cord.y + sin(data->player.rotation_angle) * step;
	if (!check_if_wall(data, x, y) && !check_if_wall2(data, x, y))
	{
		data->player.cord.x = x;
		data->player.cord.y = y;
	}
}

void	ad_move(t_data *data)
{
	double	x;
	double	y;
	int		step;

	step = data->move.ad_move * SPEED;
	x = data->player.cord.x + cos(data->player.rotation_angle + (M_PI / 2))
		* step;
	y = data->player.cord.y + sin(data->player.rotation_angle + (M_PI / 2))
		* step;
	if (!check_if_wall(data, x, y) && !check_if_wall2(data, x, y))
	{
		data->player.cord.x = x;
		data->player.cord.y = y;
	}
}

void	move_player(t_data *data)
{
	data->player.rotation_angle += data->move.rotation * M_PI / 180.0;
	if (data->move.ws_move)
		ws_move(data);
	if (data->move.ad_move)
		ad_move(data);
}
