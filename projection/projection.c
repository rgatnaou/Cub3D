/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:05:42 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/25 18:05:26 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	put_texture(t_data *data, t_cord *cord_wall, double wall_height, char dir)
{
	int	i;
	int	textOffsetX;
	int textOffsetY;
	double dist;
	(void)dir;

	// printf("horzo %d\n",data->ray.horz_hit_wall);
	// printf("vert %d\n",data->ray.vert_hit_wall);
	i = cord_wall->y;
	// if (data->ray.vert_hit_wall)
	// 	textOffsetX = cord_wall->y % data->texture.img_width;
	// else
	// 	textOffsetX = cord_wall->x % data->texture.img_width;
	if (data->ray.vert_hit_wall)
		textOffsetX = ((int)data->ray.ypoint) % SIZE_CUB;
	else
		textOffsetX = ((int)data->ray.xpoint) % SIZE_CUB;
	while (i < (wall_height + cord_wall->y))
	{
		dist = i + wall_height / 2 - HEIGHT / 2;
		// textOffsetY = ((cord_wall->y + i) * data->texture.img_height;
		textOffsetY = dist * ((double) data->texture.no.img_width / wall_height) ;
		// textOffsetY =((i - cord_wall->y) * ((float)SIZE_CUB / (int)h));
		// if (dir == 'N')
		// {
		// 	textOffsetY = dist * ((double) data->texture.no.img_height / wall_height);
		// 	my_mlx_pixel_put(&data->mlx->image, cord_wall->x, i,
		// 		data->texture.no.arr[(data->texture.no.img_width * textOffsetY) + textOffsetX]);
		// }
		// else if (dir == 'S')
		// {
		// 	textOffsetY = dist * ((double) data->texture.so.img_width / wall_height) ;
		// 	my_mlx_pixel_put(&data->mlx->image, cord_wall->x, i,
		// 		data->texture.so.arr[(data->texture.so.img_width * textOffsetY) + textOffsetX]);
		// }
		// else if (dir == 'W')
		// {
		// 	textOffsetY = dist * ((double) data->texture.we.img_width / wall_height) ;
		// 	my_mlx_pixel_put(&data->mlx->image, cord_wall->x, i,
		// 		data->texture.we.arr[(data->texture.we.img_width * textOffsetY) + textOffsetX]);
		// }
		// else if (dir == 'E')
		// {	
		// 	textOffsetY = dist * ((double) data->texture.ea.img_width / wall_height) ;
		// 	my_mlx_pixel_put(&data->mlx->image, cord_wall->x, i,
		// 		data->texture.ea.arr[(data->texture.ea.img_width * textOffsetY) + textOffsetX]);
		// }
		// else
			my_mlx_pixel_put(&data->mlx->image, cord_wall->x, i, 0x808080);
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
	y = cord_wall.y + wall_height;
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(&data->mlx->image, cord_wall.x, y, data->floor_color);
		y++;
	}
}
