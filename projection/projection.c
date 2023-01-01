/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:05:42 by ykhadiri          #+#    #+#             */
/*   Updated: 2023/01/01 14:21:59 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	put_texture(t_data *data, t_cord *cord_wall, double wall_height,
		unsigned int *arr)
{
	int		y;
	int		offset_x;
	int		offset_y;
	double	dist;

	y = cord_wall->y;
	if (data->ray.vert_hit_wall)
		offset_x = ((int)data->ray.cast.y) % SIZE_CUB;
	else
		offset_x = ((int)data->ray.cast.x) % SIZE_CUB;
	if (y < 0)
		y = 0;
	while (y < (wall_height + cord_wall->y))
	{
		dist = y - (HEIGHT / 2 - wall_height / 2);
		offset_y = dist * (IMG_HEIGHT / wall_height);
		my_mlx_pixel_put(&data->mlx.image, cord_wall->x, y, arr[(IMG_WIDTH
				* offset_y) + offset_x]);
		y++;
		if (y > HEIGHT)
			break ;
	}
}

void	set_texture(t_data *data, t_cord cord_wall, double wall_height)
{
	if (data->ray.horz_hit_wall)
	{
		if (data->ray.up)
			put_texture(data, &cord_wall, wall_height, data->texture.no.arr);
		else
			put_texture(data, &cord_wall, wall_height, data->texture.so.arr);
	}
	else
	{
		if (data->ray.right)
			put_texture(data, &cord_wall, wall_height, data->texture.ea.arr);
		else
			put_texture(data, &cord_wall, wall_height, data->texture.we.arr);
	}
}

void	projection(t_data *data, double ray_angle, int x)
{
	double	wall_height;
	t_cord	cord_wall;
	int		y;
	double	distance;

	distance = distance_to_wall(data, ray_angle);
	if (distance < 1)
		distance = 1;
	wall_height = (SIZE_CUB / distance)
		* data->projection;
	cord_wall.x = x;
	cord_wall.y = HEIGHT / 2 - wall_height / 2;
	y = 0;
	while (y < cord_wall.y)
	{
		my_mlx_pixel_put(&data->mlx.image, cord_wall.x, y, data->ceiling);
		y++;
	}
	set_texture(data, cord_wall, wall_height);
	y = cord_wall.y + wall_height;
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(&data->mlx.image, cord_wall.x, y, data->floor);
		y++;
	}
}
