/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:05:42 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/20 11:10:47 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	square1(t_data *data, t_cord *cord_wall, int h,char dir)
{
	int	i;
	int	textOffsetX;
	int textOffsetY;

	i = 0;
	textOffsetX = cord_wall->x % data->texture.img_width;
	while (i < h)
	{
			textOffsetY =((cord_wall->y + i) % data->texture.img_height);
			if (dir == 'N')
				my_mlx_pixel_put(&data->mlx->image, cord_wall->x, (cord_wall->y + i),
					data->texture.no[(data->texture.img_height * textOffsetY) + textOffsetX]);
			// else if (dir == 'S')
			// 	my_mlx_pixel_put(&data->mlx->image, cord_wall->x, (cord_wall->y + i),
			// 		data->texture.so[(data->texture.img_height * textOffsetY) + textOffsetX]);
			// else if (dir == 'W')
			// 	my_mlx_pixel_put(&data->mlx->image, cord_wall->x, (cord_wall->y + i),
			// 		data->texture.we[(data->texture.img_height * textOffsetY) + textOffsetX]);
			// else if (dir == 'E')
			// 	my_mlx_pixel_put(&data->mlx->image, cord_wall->x, (cord_wall->y + i),
			// 		data->texture.ea[(data->texture.img_height * textOffsetY) + textOffsetX]);
			else
				my_mlx_pixel_put(&data->mlx->image, cord_wall->x, (cord_wall->y + i),
					0x808080);
		i++;
	}
}

void	projection(t_data *data, double ray_angle, int i)
{
	double	dis_to_prj_wall;
	double	wall_height;
	t_cord cord_wall;

	dis_to_prj_wall = (WIDTH / 2) / tan(FOV / 2);
	wall_height = (SIZE_CUB / distance_to_wall(data, ray_angle))
		* dis_to_prj_wall;
	
	cord_wall.x = i;
	cord_wall.y = (HEIGHT - wall_height) / 2;
	if (data->ray.horz_hit_wall)
	{
		if (data->ray.up_ray)
			square1(data, &cord_wall , wall_height, 'N');
		else
			square1(data, &cord_wall , wall_height, 'S');
	}
	else
	{
		if (data->ray.right_ray)
			square1(data, &cord_wall , wall_height, 'E');
		else
			square1(data, &cord_wall , wall_height, 'W');
	}
}
