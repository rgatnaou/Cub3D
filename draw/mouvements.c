/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:48:51 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/04 19:21:05 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_top_wall(t_data *data)
{
	int x;
	int y;

	y = ((data->player.cord.y - SPEED)/ SIZE_CUB);
	x = (data->player.cord.x / SIZE_CUB);

	if (y <= 0)
		return 0;
	if (data->map[y][x] == '1')
			return 0;
	data->map[y + 1][x] = '0';
	data->player.cord.y -= SPEED;
	return (1);
}

int	check_down_wall(t_data *data)
{
	int x;
	int y;

	y = ((data->player.cord.y + 20)/ SIZE_CUB);
	x = (data->player.cord.x / SIZE_CUB);

	if (y <= 0)
		return 0;
	if (data->map[y][x] == '1')
			return 0;
	data->map[y - 1][x] = '0';
	data->player.cord.y += SPEED;
	return (1);
}

int  check_right_wall(t_data *data)
{
	int x;
	int y;

	y = ((data->player.cord.y)/ SIZE_CUB);
	x = (data->player.cord.x + 20 / SIZE_CUB);

	if (y <= 0)
		return 0;
	if (data->map[y][x] == '1')
			return 0;
	data->map[y][x - 1] = '0';
	data->player.cord.x += SPEED;
	return (1);
}


int  check_left_wall(t_data *data)
{
	(void)data;
	return 0;
}

int move_player(int keycode, t_data *data)
{
	if (keycode == KEY_W && check_top_wall(data))
		draw_2d_map(data);
	if (keycode == KEY_S && check_down_wall(data))
		draw_2d_map(data);
	if (keycode == KEY_D && check_right_wall(data))
		draw_2d_map(data);
	if (keycode == KEY_ARROW_RIGHT)
	{
		data->player.rotation_angle += SPEED * M_PI / 180;
		draw_2d_map(data);
	}
	if (keycode == KEY_ARROW_LEFT)
	{
		data->player.rotation_angle -= SPEED * M_PI / 180; 
		draw_2d_map(data);
	}
	if (keycode == KEY_ARROW_TOP)
	{
		data->player.cord.x += cos(data->player.rotation_angle) * SPEED;
		data->player.cord.y += sin(data->player.rotation_angle) * SPEED;
		draw_2d_map(data);
	}
	if (keycode == KEY_ARROW_DOWN)
	{
		data->player.cord.x -= cos(data->player.rotation_angle) * SPEED;
		data->player.cord.y -= sin(data->player.rotation_angle) * SPEED;
		draw_2d_map(data);
	}
	// if (keycode == KEY_A && ->map[(int)->p[1]][(int)(->p[0] - 0.5)] != '1')
	// {

	// }
	// if (keycode == KEY_ESC)
	// 	destroy_win(data);
	return 0;
}