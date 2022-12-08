/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:45:11 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/08 20:14:14 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

double	limit_angle(double ray_angle)
{
	double angle = fmod(ray_angle, 2 * M_PI);
	if (angle < 0)
		angle += (2 * M_PI);
	return angle;
}

void	check_ray_position(t_data *data, double ray_angle)
{
	double	angle = limit_angle(ray_angle);
	if (angle > 0 && angle < M_PI)
		data->ray.down_ray = 1;
	data->ray.up_ray = !data->ray.down_ray;
	if ((angle > (M_PI / 2)) && (angle < (3 * M_PI / 2)))
		data->ray.left_ray = 1;
	data->ray.right_ray = !data->ray.left_ray;
}

void raycasting(t_data *data, double ray_angle)
{
	double	x_first_intersect;
	double	y_first_intersect;
	double	xstep;
	double	ystep;
	double	next_xintersect;
	double	next_yintersect;

	check_ray_position(data, ray_angle);
	y_first_intersect = (data->player.cord.y / SIZE_CUB) * SIZE_CUB;
	if (data->ray.down_ray)
		y_first_intersect += SIZE_CUB;
	x_first_intersect = data->player.cord.x + ((data->player.cord.y - y_first_intersect) / tan(ray_angle));
	ystep = SIZE_CUB;
	if (data->ray.up_ray)
		ystep *= -1;
	xstep = ystep / tan(ray_angle);
	if (data->ray.left_ray && xstep > 0)
		xstep *= -1;
	if (data->ray.right_ray && xstep < 0)
		xstep *= -1;
	next_xintersect = x_first_intersect;
	next_yintersect = y_first_intersect;
	if (data->ray.up_ray)
		next_yintersect--;
	// if (data->ray.down_ray)
	// 	next_yintersect++;
	while (next_xintersect >= 0 && next_xintersect <= WIDTH && next_yintersect >= 0 && next_yintersect <= HEIGHT)
	{
		if (check_if_wall(data, next_xintersect, next_yintersect))
		{
			line(data, roundf(next_xintersect), roundf(next_yintersect), RED);
			break ;
		}
		else
		{
			next_xintersect += xstep;
			next_yintersect += ystep;
		}
	}
}
