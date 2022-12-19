/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:05:42 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/19 18:44:38 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	square1(t_mlx *mlx, double x, double y, double h, double w, t_data *data, int textOffsetX)
{
	int	i;
	int	j;
	// int getfirstPixel = (HEIGHT / 2) - ((int)h / 2);
	// printf("height / 2: %d\n", HEIGHT / 2);
	// printf("height wall dv / 2: %f\n", h / 2);
	// printf("firstpixel: %d\n", getfirstPixel);
	// printf("height wall: %f\n", h);
	// exit(0);
	// int getlastPixel = (HEIGHT / 2) + ((int)h / 2);
	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{	
			int textOffsetY = i * (data->texture.img_height / (int)h);
			my_mlx_pixel_put(&mlx->image, (x + j), (y + i),
					data->texture.no[(data->texture.img_height * textOffsetY) + textOffsetX]);
			j++;
		}
		// for (j = getfirstPixel; j < getlastPixel; j++)
		// {	
		// 	int textOffsetY = (i - getfirstPixel) * (data->texture.img_height / (int)h);
		// 	my_mlx_pixel_put(&mlx->image, (x + j), (y + i),
		// 			data->texture.no[(data->texture.img_height * textOffsetY) + textOffsetX]);
		// }
		i++;
	}
}

void	projection(t_data *data, double ray_angle, int i)
{
	(void)i;
	double	dis_to_prj_wall;
	double	wall_height;
	int	textOffsetX;
	// int	textOffsetY;

	dis_to_prj_wall = (WIDTH / 2) / tan(FOV / 2);
	wall_height = (SIZE_CUB / distance_to_wall(data, ray_angle))
		* dis_to_prj_wall;
	// printf("%d\n", (int)wall_height);
	// printf("%d\n", getfirstPixel);
	
	if (data->ray.horz_hit_wall)
	{
		// if (data->ray.up_ray)
		// 	square1(data->mlx, i, (HEIGHT - wall_height) / 2, wall_height, 1,
		// 			0xffffff);
		// else
		// 	square1(data->mlx, i, (HEIGHT - wall_height) / 2, wall_height, 1,
		// 			0xc0c0c0);
		textOffsetX = (int)data->ray.xpoint % data->texture.img_width;
	}
	else
	{
		// if (data->ray.right_ray)
		// 	square1(data->mlx, i, (HEIGHT - wall_height) / 2, wall_height, 1,
		// 			0x808080);
		// else
		// 	square1(data->mlx, i, (HEIGHT - wall_height) / 2, wall_height, 1,
		// 			0x708090);
		textOffsetX = (int)data->ray.ypoint % data->texture.img_height;
	}
	square1(data->mlx, i, (HEIGHT - wall_height) / 2, wall_height, 1, data, textOffsetX);
}
