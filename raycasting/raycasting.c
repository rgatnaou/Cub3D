/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:45:11 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/09 18:10:04 by ykhadiri         ###   ########.fr       */
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

void	check_ray_position(t_data *data, double ray)
{
	data->ray.up_ray = 0;
	data->ray.right_ray = 0;
	data->ray.down_ray = 0;
	data->ray.left_ray = 0;
	if (ray > 0 && ray < M_PI)
		data->ray.down_ray = 1;
	data->ray.up_ray = !data->ray.down_ray;
	if ((ray < M_PI / 2) || (ray > ((3 * M_PI)/ 2)))
		data->ray.right_ray = 1;
	data->ray.left_ray = !data->ray.right_ray;
}

double	distance(int xplayer, int yplayer, double xpoint, double ypoint)
{
	return (sqrt(((xpoint - xplayer) * (xpoint - xplayer)) + ((ypoint - yplayer) * (ypoint - yplayer))));
}

void horizontal_raycasting(t_data *data, double ray_angle)
{
	double	x_first_intersect;
	double	y_first_intersect;
	double	xstep;
	double	ystep;
	double	next_xintersect;
	double	next_yintersect;
	data->ray.found_horz_wall = false;
	check_ray_position(data, ray_angle);
	y_first_intersect = floor(data->player.cord.y / SIZE_CUB) * SIZE_CUB;
	if (data->ray.down_ray)
		y_first_intersect += SIZE_CUB;
	x_first_intersect = data->player.cord.x + ((y_first_intersect - data->player.cord.y) / tan(ray_angle));
	ystep = SIZE_CUB;
	if (data->ray.up_ray)
		ystep *= -1;
	xstep = SIZE_CUB / tan(ray_angle);
	if (data->ray.left_ray && xstep > 0)
		xstep *= -1;
	if (data->ray.right_ray && xstep < 0)
		xstep *= -1;
	next_xintersect = x_first_intersect;
	next_yintersect = y_first_intersect;
	if (data->ray.up_ray)
		next_yintersect--;
	while (next_xintersect >= 0 && next_xintersect <= WIDTH && next_yintersect >= 0 && next_yintersect <= HEIGHT)
	{
		if (check_if_wall(data, next_xintersect, next_yintersect))
		{
			data->ray.found_horz_wall = 1;
			data->ray.xfinal_horz_coord = next_xintersect;
			data->ray.yfinal_horz_coord = next_yintersect;
			data->ray.horz_distance = distance(data->player.cord.x, data->player.cord.y, data->ray.xfinal_horz_coord, data->ray.yfinal_horz_coord);
			break ;
		}
		else
		{
			next_xintersect += xstep;
			next_yintersect += ystep;
		}
	}
}
// -- vertical
void vertical_raycasting(t_data *data, double ray_angle)
{
	double	x_first_intersect;
	double	y_first_intersect;
	double	xstep;
	double	ystep;
	double	next_xintersect;
	double	next_yintersect;

	data->ray.found_vert_wall = false;
	check_ray_position(data, ray_angle);
	x_first_intersect = (data->player.cord.x / SIZE_CUB) * SIZE_CUB;
	if (data->ray.right_ray)
		x_first_intersect += SIZE_CUB;
	y_first_intersect = data->player.cord.y + ((x_first_intersect - data->player.cord.x ) * tan(ray_angle));
	xstep = SIZE_CUB;
	if (data->ray.left_ray)
		xstep *= -1;
	ystep = xstep * tan(ray_angle);
	if (data->ray.up_ray && ystep > 0)
		ystep *= -1;
	if (data->ray.down_ray && ystep < 0)
		ystep *= -1;
	next_xintersect = x_first_intersect;
	next_yintersect = y_first_intersect;
	if (data->ray.left_ray)
		next_xintersect--;
	if (data->ray.right_ray)
		next_xintersect++;
	while (next_xintersect >= 0 && next_xintersect <= WIDTH && next_yintersect >= 0 && next_yintersect <= HEIGHT)
	{
		if (check_if_wall(data, next_xintersect, next_yintersect))
		{
			data->ray.found_vert_wall = 1;
			data->ray.xfinal_vert_coord = next_xintersect;
			data->ray.yfinal_vert_coord = next_yintersect;
			data->ray.vert_distance = distance(data->player.cord.x, data->player.cord.y, data->ray.xfinal_vert_coord, data->ray.yfinal_vert_coord);
			break ;
		}
		else
		{
			next_xintersect += xstep;
			next_yintersect += ystep;
		}
	}
}

void	raycasting(t_data *data, double ray_angle)
{
	
	horizontal_raycasting(data, ray_angle);
	vertical_raycasting(data, ray_angle);

	data->ray.xpoint = data->ray.xfinal_horz_coord;
	data->ray.ypoint = data->ray.yfinal_horz_coord;

		if (data->ray.found_vert_wall)
		{
			if (data->ray.vert_distance < data->ray.horz_distance)
			{
				data->ray.xpoint = data->ray.xfinal_vert_coord;
				data->ray.ypoint = data->ray.yfinal_vert_coord;
			}
		}
	line(data, data->ray.xpoint, data->ray.ypoint, RED);
}
