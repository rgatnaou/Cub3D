/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:48:51 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/06 13:17:15 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_if_wall(t_data *data, int x_cord_win, int y_cord_win)
{
	int	x_cor_in_map;
	int	y_cor_in_map;

	x_cor_in_map = roundf(x_cord_win / SIZE_CUB);
	y_cor_in_map = roundf(y_cord_win / SIZE_CUB);
	if (!(x_cor_in_map >= NB_CLS || y_cor_in_map >= NB_RWS)
		&& data->map[y_cor_in_map][x_cor_in_map] == '0')
		return (0);
	return (1);
}

void key_press_d(t_data *data)
{
		double angle =  data->player.rotation_angle + (M_PI/2) ;
		int x_player = roundf(data->player.cord.x + (cos(angle) * SPEED));
		int y_player = roundf(data->player.cord.y + (sin(angle) * SPEED));
		if (!check_if_wall(data, x_player, y_player))
		{	
			data->player.cord.x = x_player;
			data->player.cord.y = y_player;
		}
		draw_2d_map(data);
}

void key_press_a(t_data *data)
{
		double angle =  data->player.rotation_angle - (M_PI/2) ;
		int x_player = roundf(data->player.cord.x + (cos(angle) * SPEED));
		int y_player = roundf(data->player.cord.y + (sin(angle) * SPEED));
		if (!check_if_wall(data, x_player, y_player))
		{	
			data->player.cord.x = x_player;
			data->player.cord.y = y_player;
		}
		draw_2d_map(data);
}

void key_press_s(t_data *data)
{
		int x_player = roundf(data->player.cord.x
				- cos(data->player.rotation_angle) * SPEED);
		int y_player = roundf(data->player.cord.y
				- sin(data->player.rotation_angle) * SPEED);
		if (!check_if_wall(data, x_player, y_player))
		{
			data->player.cord.x = x_player;
			data->player.cord.y = y_player;
		}
		draw_2d_map(data);
}
void key_press_w(t_data *data)
{
	int x_player = roundf(data->player.cord.x
			+ cos(data->player.rotation_angle) * SPEED);
	int y_player = roundf(data->player.cord.y
			+ sin(data->player.rotation_angle) * SPEED);
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

void	raycasting(t_data *data)
{
	int	i;
	double	ray_angle;

	i = 0;
	ray_angle = data->player.rotation_angle - (FOV / 2);
	while (i <( WIDTH))
	{
		line(data, roundf(data->player.cord.x + cos(ray_angle) * 50), roundf(data->player.cord.y + sin(ray_angle) * 50), RED);
		ray_angle += (FOV / WIDTH);
		i++;
	}
}