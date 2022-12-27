/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:26:29 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/27 13:42:09 by rgatnaou         ###   ########.fr       */
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

void	draw_2d(t_data *data)
{
	int	i;
	int	j;
	t_cord	start;

	draw_3d(data);
	start.x = data->player.cord.x / SIZE_CUB;
	start.y = data->player.cord.y / SIZE_CUB;

	start.y = (start.y - 10 < 0)? 0 : start.y - 10;
	start.x = (start.x - 10 < 0)? 0 : start.x - 10;
	i = start.y;
	while (i < start.y + 21 && data->map[i])
	{
		j = start.x;
		while (data->map[i][j] && j < start.x + 31 && j < (int)ft_strlen(data->map[i]))
		{
			if (data->map[i][j] == '1')
				square(&data->mlx, ((j - start.x) * SIZE_CUB) , ((i - start.y) * SIZE_CUB) , 0x000000);
			else if (data->map[i][j] == '0')
				square(&data->mlx, ((j - start.x) * SIZE_CUB), ((i - start.y)* SIZE_CUB), WHITE);
			j++;
		}
		i++;
	}
	start.x = data->player.cord.x - (start.x * SIZE_CUB);
	start.y = data->player.cord.y - (start.y * SIZE_CUB); 
	draw_player(data ,&start);
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
