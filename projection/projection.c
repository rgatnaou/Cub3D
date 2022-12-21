/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:05:42 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/21 18:16:14 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	put_texture(t_data *data, t_cord *cord_wall, double wall_height, char dir)
{
	int	i;
	int	textOffsetX;
	int textOffsetY;
	double dist;

	// printf("horzo %d\n",data->ray.horz_hit_wall);
	// printf("vert %d\n",data->ray.vert_hit_wall);
	i = cord_wall->y;
	// if (data->ray.vert_hit_wall)
	// 	textOffsetX = cord_wall->y % data->texture.img_width;
	// else
	// 	textOffsetX = cord_wall->x % data->texture.img_width;
	if (data->ray.vert_hit_wall)
		textOffsetX = (int)data->ray.ypoint % data->texture.img_width;
	else
		textOffsetX = (int)data->ray.xpoint % data->texture.img_width;
	while (i < (wall_height + cord_wall->y))
	{
		//textOffsetY = ((cord_wall->y + i) * data->texture.img_height;
		dist = i + wall_height / 2 - HEIGHT / 2;
		textOffsetY = dist * ((double)data->texture.img_width / wall_height) ;
		// textOffsetY =((i - cord_wall->y) * ((float)SIZE_CUB / (int)h));
		if (dir == 'N')
			my_mlx_pixel_put(&data->mlx->image, cord_wall->x, i,
				data->texture.no[(data->texture.img_width * textOffsetY) + textOffsetX]);
		else if (dir == 'S')
			my_mlx_pixel_put(&data->mlx->image, cord_wall->x, i,
				data->texture.so[(data->texture.img_height * textOffsetY) + textOffsetX]);
		else if (dir == 'W')
			my_mlx_pixel_put(&data->mlx->image, cord_wall->x, i,
				data->texture.we[(data->texture.img_height * textOffsetY) + textOffsetX]);
		else if (dir == 'E')
			my_mlx_pixel_put(&data->mlx->image, cord_wall->x, i,
				data->texture.ea[(data->texture.img_height * textOffsetY) + textOffsetX]);
		else
			my_mlx_pixel_put(&data->mlx->image, cord_wall->x, (i), 0x808080);
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
	// if (cord_wall.y < 0)
	// 	cord_wall.y = 0;
	if (data->ray.horz_hit_wall)
	{
		if (data->ray.up_ray)
			put_texture(data, &cord_wall , wall_height, 'N');
		else
			put_texture(data, &cord_wall , wall_height, 'S');
	}
	else
	{
		if (data->ray.right_ray)
			put_texture(data, &cord_wall , wall_height, 'E');
		else
			put_texture(data, &cord_wall , wall_height, 'W');
	}
}
