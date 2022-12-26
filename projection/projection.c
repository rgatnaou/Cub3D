/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:05:42 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/26 18:48:14 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	put_texture(t_data *data, t_cord *cord_wall, double wall_height, unsigned int *arr)
{
	int	i;
	int	textOffsetX;
	int textOffsetY;
	double dist;


	i = cord_wall->y;

	if (data->ray.vert_hit_wall)
		textOffsetX = ((int)data->ray.cast.y) % SIZE_CUB;
	else
		textOffsetX = ((int)data->ray.cast.x) % SIZE_CUB;
	while (i < (wall_height + cord_wall->y))
	{
		dist = i + wall_height / 2 - HEIGHT / 2;
		textOffsetY = dist * ((double) data->texture.no.img_width / wall_height) ;

			textOffsetY = dist * ((double) data->texture.no.img_height / wall_height);
			my_mlx_pixel_put(&data->mlx->image, cord_wall->x, i,
				arr[(data->texture.no.img_width * textOffsetY) + textOffsetX]);
		i++;
	}
}

void	projection(t_data *data, double ray_angle, int x)
{
	double	dis_projection;
	double	wall_height;
	t_cord	cord_wall;
	int 	y;

	dis_projection = (WIDTH / 2) / tan(FOV / 2);
	wall_height = (SIZE_CUB / distance_to_wall(data, ray_angle))
		* dis_projection; 
	
	cord_wall.x = x;
	cord_wall.y = HEIGHT / 2 - wall_height / 2;
	y = 0;
	while (y < cord_wall.y)
	{
		my_mlx_pixel_put(&data->mlx->image, cord_wall.x, y, data->ceiling_color);
		y++;
	}
	if (data->ray.horz_hit_wall)
	{
		if (data->ray.up)
			put_texture(data, &cord_wall , wall_height, data->texture.no.arr);
		else
			put_texture(data, &cord_wall , wall_height, data->texture.so.arr);
	}
	else
	{
		if (data->ray.right)
			put_texture(data, &cord_wall , wall_height, data->texture.ea.arr);
		else
			put_texture(data, &cord_wall , wall_height, data->texture.we.arr);
	}
	y = cord_wall.y + wall_height;
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(&data->mlx->image, cord_wall.x, y, data->floor_color);
		y++;
	}
}
