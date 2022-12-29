/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:45:11 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/29 15:49:33 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

double	distance_to_wall(t_data *data, double ray_angle)
{
	double	final_distance;

	check_ray_position(data, ray_angle);
	data->ray.horz_hit_wall = horizontal_raycasting(data, ray_angle);
	data->ray.vert_hit_wall = vertical_raycasting(data, ray_angle);
	if (data->ray.vert_distance < data->ray.horz_distance)
	{
		data->ray.cast.x = data->ray.vert.x;
		data->ray.cast.y = data->ray.vert.y;
		data->ray.horz_hit_wall = false;
	}
	else
	{
		data->ray.cast.x = data->ray.horz.x;
		data->ray.cast.y = data->ray.horz.y;
		data->ray.vert_hit_wall = false;
	}
	final_distance = distance(&data->player.cord, &data->ray.cast)
		* cos(ray_angle - data->player.rotation_angle);
	return (final_distance);
}

void	draw_3d(t_data *data)
{
	int		x;
	double	ray_angle;

	x = 0;
	ray_angle = data->player.rotation_angle - (data->fov / 2);
	while (x < WIDTH)
	{
		projection(data, limit_angle(ray_angle), x);
		ray_angle += data->fov / WIDTH;
		x++;
	}
}
