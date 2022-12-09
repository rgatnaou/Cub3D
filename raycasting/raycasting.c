/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:45:11 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/09 19:44:02 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

bool	found_horz_hit_wall(t_data *data, double x_intersect,
		double y_intersect, double xstep, double ystep)
{
	while (x_intersect >= 0 && x_intersect <= WIDTH && y_intersect >= 0
		&& y_intersect <= HEIGHT)
	{
		if (check_if_wall(data, x_intersect, y_intersect))
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
	while (x_intersect >= 0 && x_intersect <= WIDTH && y_intersect >= 0
		&& y_intersect <= HEIGHT)
	{
		if (check_if_wall(data, x_intersect, y_intersect))
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
	if (data->ray.left_ray && xstep > 0)
		xstep *= -1;
	if (data->ray.right_ray && xstep < 0)
		xstep *= -1;
	if (data->ray.up_ray)
		y_intersect--;
	return (found_horz_hit_wall(data, x_intersect, y_intersect, xstep, ystep));
}

bool	vertical_raycasting(t_data *data, double ray_angle)
{
	double	x_intersect;
	double	y_intersect;
	double	xstep;
	double	ystep;

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
	if (data->ray.left_ray)
		x_intersect--;
	if (data->ray.right_ray)
		y_intersect++;
	return (found_vert_hit_wall(data, x_intersect, y_intersect, xstep, ystep));
}

void	raycasting(t_data *data, double ray_angle)
{
	double	xpoint;
	double	ypoint;

	horizontal_raycasting(data, ray_angle);
	vertical_raycasting(data, ray_angle);
	xpoint = data->ray.xfinal_horz_coord;
	ypoint = data->ray.yfinal_horz_coord;
	if (vertical_raycasting(data, ray_angle))
	{
		if (data->ray.vert_distance < data->ray.horz_distance)
		{
			xpoint = data->ray.xfinal_vert_coord;
			ypoint = data->ray.yfinal_vert_coord;
		}
	}
	line(data, xpoint, ypoint, RED);
}

void	draw_rays(t_data *data)
{
	int		i;
	double	ray_angle;

	i = 0;
	ray_angle = data->player.rotation_angle - (FOV / 2);
	while (i < WIDTH)
	{
		raycasting(data, limit_angle(ray_angle));
		ray_angle += (FOV / WIDTH);
		i++;
	}
}
