/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_in_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:26:29 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/01 19:06:50 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_square(t_mlx *mlx, int x, int y, int color)
{
	float i;
	float j;

	i = 0;
	while(i < 9)
	{
		j = 0;
		while (j < 9)
		{
			my_mlx_pixel_put(&mlx->img, x + j, y + i, color);
			j ++;
		}
		i ++;
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

int destroy_win(t_mlx *m)
{
	mlx_destroy_window(m->mlx,m->win);
	exit(0);
}

// int func(t_mlx *m)
// {
// 	player_draw(m);
// 	printf("color :%f : %d\n", m->p[1],(int)m->p[1]);
// 	return 1;
// }

int key_hook(int keycode, t_mlx *m)
{
	if (keycode == KEY_W && m->map[(int)(m->p[1] - 0.5)][(int)m->p[0]] != '1')
	{
		draw_square(m ,(m->p[0] * 8) + 10,(m->p[1]*8) + 10, 0);
		m->p[1] -= 0.5;
	}
	if (keycode == KEY_S && m->map[(int)(m->p[1] + 0.5)][(int)m->p[0]] != '1')
	{
		draw_square(m ,(m->p[0] * 8) + 10,(m->p[1]*8) + 10, 0);
		m->p[1] += 0.5;
	}
	if (keycode == KEY_D && m->map[(int)m->p[1]][(int)(m->p[0] + 0.5)] != '1')
	{
		draw_square(m ,(m->p[0] * 8) + 10,(m->p[1]*8) + 10, 0);
		m->p[0] += 0.5;
	}
	if (keycode == KEY_A && m->map[(int)m->p[1]][(int)(m->p[0] - 0.5)] != '1')
	{
		draw_square(m ,(m->p[0] * 8) + 10,(m->p[1]*8) + 10, 0);
		m->p[0] -= 0.5;
	}
	if (keycode == KEY_ESC)
		destroy_win(m);
	return 0;
}

void draw_2d_map(t_mlx *mlx)
{
	// mlx_clear_window(mlx->mlx, mlx->win);
	int i = 0;
	int j = 0;

	while (mlx->map[i])
	{
		j = 0;
		while (mlx->map[i][j])
		{
			if (mlx->map[i][j] == '1')
				draw_square(mlx, (j * 10) + 10, (i * 10) + 10, WHITE);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 10, 10);
}

int draw(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "cub3D");
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img,
			&mlx->img.bits_per_pixel, &mlx->img.line_length,
			&mlx->img.endian);
	draw_2d_map(mlx);
	// mlx_hook(mlx->win, 17, 0L,&destroy_win, mlx);
	// mlx_hook(mlx->win, 02, 0L, &key_hook, mlx);
	// mlx_loop_hook(mlx->mlx, func, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}