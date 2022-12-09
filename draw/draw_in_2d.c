/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_in_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:26:29 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/09 19:02:06 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// void	draw_terangle_NO(t_mlx *m, int x, int y, int z, int color)
// {
// 	int i;
// 	int j;

// 	i = 2;
// 	while(i < 7)
// 	{
// 		j = 0;
// 		while (j < 7)
// 		{
// 			if (j >= z && j + z < 7 && z >= 0)
// 				mlx_pixel_put(m->mlx , m->win, x + j , y + i, color);
// 			j++;
// 		}
// 		z--;
// 		i++;
// 	}
// }
// void player_draw(t_mlx *m)
// {
// 	// draw_square(m ,(m->p[0] * 8) + 10,(m->p[1]*8) + 10, 0xFF0000);
// 	// int i;
// 	// int j;
// 	// int z = 3;
// 	int x ;
// 	int y;
// 	x = (m->p[0] * 8) + 10;
// 	y = (m->p[1] * 8) + 10;
// 	draw_square(m,x,y,0xFF0000);
// 	// i = 0;
// 	// while(i < 6)
// 	// {
// 	// 	j = 0;
// 	// 	while (j < 7)
// 	// 	{
// 	// 		if (j >= z && j + z < 7 && z >= 0)
// 	// 		{
// 	// 			printf ("*");
// 	// 			mlx_pixel_put(m->mlx , m->win, x + j , y + i, 0xFF0000);
// 	// 		}
// 	// 		j++;
// 	// 	}
// 	// 		z--;
// 	// 	printf("\n");
// 	// 	i++;
// 	// }
// }

int	destroy_win(t_parse *parsing)
{
	mlx_destroy_image(parsing->data->mlx->init, parsing->data->mlx->image.img);
	mlx_destroy_window(parsing->data->mlx->init, parsing->data->mlx->win);
	free_parse(parsing);
	exit(0);
}

// int func(t_mlx *m)
// {
// 	player_draw(m);
// 	printf("color :%f : %d\n", m->p[1],(int)m->p[1]);
// 	return (1);
// }

void	draw_2d_map(t_data *data)
{
	int	i;
	int	j;
	int	cube_x;
	int	cube_y;

	mlx_clear_window(data->mlx->init, data->mlx->win);
	i = 0;
	while (i < NB_RWS)
	{
		j = 0;
		while (data->map[i][j])
		{
			cube_x = j * SIZE_CUB;
			cube_y = i * SIZE_CUB;
			if (data->map[i][j] == '1')
				square(data->mlx, cube_x, cube_y, BLUE);
			else if (data->map[i][j] == '0')
				square(data->mlx, cube_x, cube_y, WHITE);
			j++;
		}
		i++;
	}
	draw_player(data);
	mlx_put_image_to_window(data->mlx, data->mlx->win, data->mlx->image.img, 0,
		0);
}

int	draw(t_parse *parsing)
{
	t_data	*data;

	data = parsing->data;
	data->mlx->init = mlx_init();
	data->mlx->win = mlx_new_window(data->mlx->init, WIDTH, HEIGHT, "cub3D");
	data->mlx->image.img = mlx_new_image(data->mlx->init, WIDTH, HEIGHT);
	data->mlx->image.addr = mlx_get_data_addr(data->mlx->image.img,
			&data->mlx->image.bits_per_pixel,
			&data->mlx->image.line_length,
			&data->mlx->image.endian);
	data->map[data->player.cord.y][data->player.cord.x] = '0';
	data->player.cord.x = (data->player.cord.x * SIZE_CUB) + 10;
	data->player.cord.y = (data->player.cord.y * SIZE_CUB) + 10;
	if (data->player.direction == 'N')
		data->player.rotation_angle = 270 * M_PI / 180;
	else if (data->player.direction == 'S')
		data->player.rotation_angle = M_PI / 2;
	else if (data->player.direction == 'W')
		data->player.rotation_angle = M_PI;
	else if (data->player.direction == 'E')
		data->player.rotation_angle = 0;
	draw_2d_map(data);
	mlx_hook(data->mlx->win, 17, 0L, &destroy_win, parsing);
	mlx_hook(data->mlx->win, 02, 0L, &move_player, parsing);
	// mlx_loop_hook(mlx->init, func, mlx);
	mlx_loop(data->mlx->init);
	return (0);
}
