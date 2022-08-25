/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:26:29 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/08/25 17:36:20 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
void	draw_square(t_data *m, int x, int y, int color)
{
	float i;
	float j;
	
	i = 0;
	while(i < 7)
	{
		j = 0;
		while (j < 7)
		{
			mlx_pixel_put(m->mlx , m->win, x + j , y + i, color);
			j += 0.5;
		}
		i += 0.5;
	}
}

// void	draw_terangle_NO(t_data *m, int x, int y, int z, int color)
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
void player_draw(t_data *m)
{
	// draw_square(m ,(m->p[0] * 8) + 10,(m->p[1]*8) + 10, 0xFF0000);
	// int i;
	// int j;
	// int z = 3;
	int x ;
	int y;
	x = (m->p[0] * 8) + 10;
	y = (m->p[1] * 8) + 10;
	draw_square(m,x,y,0xFF0000);
	// i = 0;
	// while(i < 6)
	// {
	// 	j = 0;
	// 	while (j < 7)
	// 	{
	// 		if (j >= z && j + z < 7 && z >= 0)
	// 		{
	// 			printf ("*");
	// 			mlx_pixel_put(m->mlx , m->win, x + j , y + i, 0xFF0000);
	// 		}
	// 		j++;
	// 	}
	// 		z--;
	// 	printf("\n");
	// 	i++;
	// }
}
void mini_map(t_data *m)
{
	int i;
	int j;

	i = 0;
	while (m->map[i])
	{
		j = 0;
		while (m->map[i][j])
		{
			if (m->map[i][j] == '1')
				draw_square(m ,(j*8) + 10,(i*8) + 10, 0xFFFFFF);
			j++;
		}
		i++;
	}
}
int destroy_win(t_data *m)
{
	mlx_destroy_window(m->mlx,m->win);
	exit(0);
}

int func(t_data *m)
{
	player_draw(m);
	printf("color :%f : %d\n", m->p[1],(int)m->p[1]);
	return 1;
}

int key_hook(int keycode, t_data *m)
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

int draw(t_data *m)
{
	mini_map(m);
	mlx_hook(m->win, 17, 0L,&destroy_win, m);
	mlx_hook(m->win, 02, 0L, &key_hook, m);
	mlx_loop_hook(m->mlx, func, m);
	mlx_loop(m->mlx);
	return (0);
}