/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:45:11 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/19 14:04:10 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

bool	found_horz_hit_wall(t_data *data, double x_intersect,
		double y_intersect, double xstep, double ystep)
{
	data->ray.xfinal_horz_coord = 0;
	data->ray.yfinal_horz_coord = 0;
	
	while (x_intersect >= 0 && x_intersect <= WIDTH && y_intersect >= 0
		&& y_intersect <= HEIGHT)
	{
		if (check_if_wall(data, x_intersect, y_intersect - data->ray.up_ray))
		{
			data->ray.xfinal_horz_coord = x_intersect;
			data->ray.yfinal_horz_coord = y_intersect;
			data->ray.horz_distance = distance(data->player.cord.x,
					data->player.cord.y,
					data->ray.xfinal_horz_coord,
					data->ray.yfinal_horz_coord);
			return (true);
		}
		else
		{
			x_intersect += xstep;
			y_intersect += ystep;
		}
	}
	return (false);
}

bool	found_vert_hit_wall(t_data *data, double x_intersect,
		double y_intersect, double xstep, double ystep)
{
	data->ray.xfinal_vert_coord = 0;
	data->ray.yfinal_vert_coord = 0;

	while (x_intersect >= 0 && x_intersect <= WIDTH && y_intersect >= 0
		&& y_intersect <= HEIGHT)
	{
		if (check_if_wall(data, x_intersect - data->ray.left_ray, y_intersect))
		{
			data->ray.xfinal_vert_coord = x_intersect;
			data->ray.yfinal_vert_coord = y_intersect;
			data->ray.vert_distance = distance(data->player.cord.x,
					data->player.cord.y,
					data->ray.xfinal_vert_coord,
					data->ray.yfinal_vert_coord);
			return (true);
		}
		else
		{
			x_intersect += xstep;
			y_intersect += ystep;
		}
	}
	return (false);
}

bool	horizontal_raycasting(t_data *data, double ray_angle)
{
	double	x_intersect;
	double	y_intersect;
	double	xstep;
	double	ystep;

	data->ray.horz_distance = INT_MAX;
	check_ray_position(data, ray_angle);
	y_intersect = floor(data->player.cord.y / SIZE_CUB) * SIZE_CUB;
	if (data->ray.down_ray)
		y_intersect += SIZE_CUB;
	x_intersect = data->player.cord.x + ((y_intersect - data->player.cord.y)
			/ tan(ray_angle));
	ystep = SIZE_CUB;
	if (data->ray.up_ray)
		ystep *= -1;
	xstep = SIZE_CUB / tan(ray_angle);
	if ((data->ray.left_ray && xstep > 0) || (data->ray.right_ray && xstep < 0))
		xstep *= -1;
	return (found_horz_hit_wall(data, x_intersect, y_intersect, xstep, ystep));
}

bool	vertical_raycasting(t_data *data, double ray_angle)
{
	double	x_intersect;
	double	y_intersect;
	double	xstep;
	double	ystep;
	
	data->ray.vert_distance = INT_MAX;
	check_ray_position(data, ray_angle);
	x_intersect = (data->player.cord.x / SIZE_CUB) * SIZE_CUB;
	if (data->ray.right_ray)
		x_intersect += SIZE_CUB;
	y_intersect = data->player.cord.y + ((x_intersect - data->player.cord.x)
			* tan(ray_angle));
	xstep = SIZE_CUB;
	if (data->ray.left_ray)
		xstep *= -1;
	ystep = xstep * tan(ray_angle);
	if (data->ray.up_ray && ystep > 0)
		ystep *= -1;
	if (data->ray.down_ray && ystep < 0)
		ystep *= -1;
	return (found_vert_hit_wall(data, x_intersect, y_intersect, xstep, ystep));
}

double	distance_to_wall(t_data *data, double ray_angle)
{
	double	final_distance;

	data->ray.horz_hit_wall = horizontal_raycasting(data, ray_angle);
	data->ray.vert_hit_wall = vertical_raycasting(data, ray_angle);
	
	if(data->ray.horz_hit_wall)
	{
		data->ray.ypoint = data->ray.yfinal_horz_coord;
		data->ray.xpoint = data->ray.xfinal_horz_coord;
	}
	if (data->ray.horz_hit_wall && data->ray.vert_hit_wall)
	{
		if (data->ray.vert_distance < data->ray.horz_distance)
		{
			data->ray.xpoint = data->ray.xfinal_vert_coord;
			data->ray.ypoint = data->ray.yfinal_vert_coord;
			data->ray.horz_hit_wall = false;
		}
	}
	else if (data->ray.vert_hit_wall)
	{
		data->ray.xpoint = data->ray.xfinal_vert_coord;
		data->ray.ypoint = data->ray.yfinal_vert_coord;
	}
	final_distance = distance(data->player.cord.x, data->player.cord.y, data->ray.xpoint, data->ray.ypoint) * cos(ray_angle - data->player.rotation_angle);
	return (final_distance);
}
void	draw_3d(t_data *data)
{
	int		i;
	int		j;
	double	ray_angle;

	i = 0;
	while( i < HEIGHT)
	{
		j = 0;
		while(j < WIDTH)
		{
			if ( i < HEIGHT / 2)
				my_mlx_pixel_put(&data->mlx->image,j,i,data->ceiling_color);
			else 
				my_mlx_pixel_put(&data->mlx->image,j,i,data->floor_color);
			j++;
		}
		i++;
	}
	i = 0;
	ray_angle = data->player.rotation_angle - (FOV / 2);
	while (i < WIDTH)
	{
		projection(data, limit_angle(ray_angle), i);
		ray_angle += (FOV / WIDTH);
		i++;
	}
}
