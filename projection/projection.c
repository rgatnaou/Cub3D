/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:05:42 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/17 15:51:44 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	square1(t_mlx *mlx, double x, double y, double h, double w, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			my_mlx_pixel_put(&mlx->image, (x + j), (y + i), color);
			j++;
		}
		i++;
	}
}

void	projection(t_data *data, double ray_angle, int i)
{
	double	dis_to_prj_wall;
	double	wall_height;

	dis_to_prj_wall = (WIDTH / 2) / tan(FOV / 2);
	wall_height = (SIZE_CUB / distance_to_wall(data, ray_angle))
		* dis_to_prj_wall;
	if (data->ray.horz_hit_wall)
	{
		if (data->ray.up_ray)
			square1(data->mlx, i, (HEIGHT - wall_height) / 2, wall_height, 1,
					0xffffff);
		else
			square1(data->mlx, i, (HEIGHT - wall_height) / 2, wall_height, 1,
					0xc0c0c0);
	}
	else
	{
		if (data->ray.right_ray)
			square1(data->mlx, i, (HEIGHT - wall_height) / 2, wall_height, 1,
					0x808080);
		else
			square1(data->mlx, i, (HEIGHT - wall_height) / 2, wall_height, 1,
					0x708090);
	}
}
