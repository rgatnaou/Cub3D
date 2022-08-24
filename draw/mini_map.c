/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:26:29 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/08/24 20:12:12 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
void	draw_square(t_data *m, int x, int y, int color)
{
	int i;
	int j;
	
	i = 0;
	while(i < 7)
	{
		j = 0;
		while (j < 7)
		{
			mlx_pixel_put(m->mlx , m->win, x + j , y + i, color);
			j++;
		}
		i++;
	}
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
			if (m->map[i][j] == 'N' || m->map[i][j] == 'S' || m->map[i][j] == 'E' || m->map[i][j] == 'W')
			{
				draw_square(m ,(j*8) + 10,(i*8) + 10, 0xFF0000);
				m->p[0] = j;
				m->p[1] = i;
			}
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

int func(t_data *data)
{
	printf("color :%d\n", data->color[0]);
	return 1;
}

int key_hook(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->color[0]++;
	return 0;
}

int draw(t_data *m)
{
	mini_map(m);
	mlx_hook(m->win, 17, 0L,&destroy_win, m);
	m->color[0] = 0;
	mlx_key_hook(m->win, &key_hook, m);
	mlx_loop_hook(m->mlx, func, m);
	mlx_loop(m->mlx);
	return (0);
}