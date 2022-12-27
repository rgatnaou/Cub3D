/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:26:29 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/27 18:20:23 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_minimap(t_data *data, t_cord start, int i)
{
	int	j;

	while (i < start.y + 21 && data->map[i])
	{
		j = start.x;
		while (data->map[i][j] && j < start.x + 31
			&& j < (int)ft_strlen(data->map[i]))
		{
			if (data->map[i][j] == '1')
				square(&data->mlx, ((j - start.x) * SIZE_CUB), ((i - start.y)
						* SIZE_CUB), 0x000000);
			else if (data->map[i][j] == '0')
				square(&data->mlx, ((j - start.x) * SIZE_CUB), ((i - start.y)
						* SIZE_CUB), WHITE);
			j++;
		}
		i++;
	}
}

void	draw_2d(t_data *data)
{
	int		i;
	t_cord	start;

	draw_3d(data);
	start.x = data->player.cord.x / SIZE_CUB;
	start.y = data->player.cord.y / SIZE_CUB;
	if (start.x - 10 < 0)
		start.x = 0;
	else
		start.x -= 10;
	if (start.y - 10 < 0)
		start.y = 0;
	else
		start.y -= 10;
	i = start.y;
	draw_minimap(data, start, i);
	start.x = data->player.cord.x - (start.x * SIZE_CUB);
	start.y = data->player.cord.y - (start.y * SIZE_CUB);
	draw_player(data, &start);
	mlx_put_image_to_window(&data->mlx, data->mlx.win, data->mlx.image.img, 0,
		0);
}

int	rendering(t_data *data)
{
	if (data->move.ws_move != -1 || data->move.ad_move != -1
		|| data->move.rotation != -1)
	{
		move_player(data);
		ft_bzero(data->mlx.image.addr, data->mlx.image.line_length * HEIGHT);
		draw_2d(data);
	}
	return (0);
}

int	draw(t_data *data)
{
	data->mlx.init = mlx_init();
	data->mlx.win = mlx_new_window(data->mlx.init, WIDTH, HEIGHT, "cub3D");
	data->mlx.image.img = mlx_new_image(data->mlx.init, WIDTH, HEIGHT);
	data->mlx.image.addr = mlx_get_data_addr(data->mlx.image.img,
			&data->mlx.image.bits_per_pixel,
			&data->mlx.image.line_length,
			&data->mlx.image.endian);
	draw_2d(data);
	mlx_hook(data->mlx.win, 02, 0L, &key_pressed, data);
	mlx_hook(data->mlx.win, 03, 0L, &key_release, data);
	mlx_hook(data->mlx.win, 17, 0L, &destroy_win, data);
	mlx_loop_hook(data->mlx.init, &rendering, data);
	mlx_loop(data->mlx.init);
	return (0);
}
