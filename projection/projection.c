/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:05:42 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/13 19:34:51 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	square1(t_mlx *mlx, double x, double y, double h, int color)
{
	int	i;
	int	j;

	i = 0;
	// printf("%f\n", h);
	while (i <= h)
	{
		j = 0;
		while (j <=  SIZE_CUB)
		{
			// if ((j > size_cube_minimap - 1) || (i > size_cube_minimap - 1) || i < 1 || j < 1)
			// 	my_mlx_pixel_put(&mlx->image, (x + j), (y + i), 0x00ffff);
			// else
				// printf("x :%f   y :%f\n",(x + j), (y + i));
				my_mlx_pixel_put(&mlx->image, (x + j), (y + i), color);
			j++;
		}
		i++;
	}
}
void	projection(t_data *data, double ray_angle, int i)
{

	double	dis_to_prj_wall;
	double	wall_height = 0;
		dis_to_prj_wall = (WIDTH / 2) / tan(FOV / 2);
		double distance = raycasting(data, ray_angle);
		// if(distance <= 0)
		// 	puts("here");
		wall_height = (SIZE_CUB / distance) * dis_to_prj_wall;
		// square(data->mlx, (i / MINIMAP_FACTOR), ((HEIGHT / 2) - (wall_height / 2)) / MINIMAP_FACTOR, 0xffffff);
		square1(data->mlx, i, (HEIGHT - wall_height) / 2, wall_height , 0xffffff);
}
