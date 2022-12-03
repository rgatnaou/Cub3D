/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_in_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:26:29 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/03 17:06:57 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;	
	}
}

void	draw_square(t_mlx *mlx, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while(i <= SIZE_CUB )
	{
		j = 0;
		while (j <= SIZE_CUB)
		{
			if ((x + j) < WIDTH && (y+ i) < HEIGHT)
				my_mlx_pixel_put(&mlx->image, (x + j), (y + i), color);
			j++;
		}
		i++;
	}
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

int destroy_win(t_parse *parsing)
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
// 	return 1;
// }

// int	check_top_wall(t_cord *coord, char **map)
// {
// 	int x;
// 	int y;
// 	y = (coord->y / SIZE_CUB) - 1;
// 	x = (coord->x / SIZE_CUB);

// 	if(y <= 0)
// 		return 0;
// 	if (map[y][x] == '1')
// 		return 0;
// 	return 1;
// }

// int move_player(int keycode, t_data *data)
// {
// 	t_cord coord = data->player.cord;

// 	if (keycode == KEY_W && check_top_wall(&coord,data->map))
// 	{
		
// 	}
// 	if (keycode == KEY_S && ->map[(int)(->p[1] + 0.5)][(int)->p[0]] != '1')
// 	{

// 	}
// 	if (keycode == KEY_D && ->map[(int)->p[1]][(int)(->p[0] + 0.5)] != '1')
// 	{

// 	}
// 	if (keycode == KEY_A && ->map[(int)->p[1]][(int)(->p[0] - 0.5)] != '1')
// 	{

// 	}
// 	if (keycode == KEY_ESC)
// 		destroy_win(data);
// 	return 0;
// }

void draw_2d_map(t_data *data)
{
	int i;
	int j;

	mlx_clear_window(data->mlx->init, data->mlx->win);
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
				draw_square(data->mlx,j * SIZE_CUB, i * SIZE_CUB, BLUE);
			else if(data->map[i][j] == '0')
				draw_square(data->mlx,j * SIZE_CUB, i * SIZE_CUB, WHITE);
			j++;
		}
		i++;
	}
	data->player.cord.x = data->player.cord.x * SIZE_CUB;
	data->player.cord.y = data->player.cord.y * SIZE_CUB;
	draw_square(data->mlx, data->player.cord.x , data->player.cord.y, RED);
	mlx_put_image_to_window(data->mlx, data->mlx->win, data->mlx->image.img, 0, 0);
}

int draw(t_parse *parsing)
{
	t_data *data = parsing->data;
	data->mlx->init = mlx_init();
	data->mlx->win = mlx_new_window(data->mlx->init, WIDTH, HEIGHT, "cub3D");
	data->mlx->image.img = mlx_new_image(data->mlx->init, WIDTH, HEIGHT);
	data->mlx->image.addr = mlx_get_data_addr(data->mlx->image.img,
			&data->mlx->image.bits_per_pixel, &data->mlx->image.line_length,
			&data->mlx->image.endian);
	draw_2d_map(data);
	mlx_hook(data->mlx->win, 17, 0L,&destroy_win, parsing);
	// mlx_hook(data->mlx->win, 02, 0L, &move_player, data->mlx);
	// mlx_loop_hook(mlx->init, func, mlx);
	mlx_loop(data->mlx->init);
	return (0);
}