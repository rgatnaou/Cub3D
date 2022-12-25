/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:53:53 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/25 19:14:54 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

double	limit_angle(double ray_angle)
{
	double	angle;

	angle = fmod(ray_angle, 2 * M_PI);
	if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
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
	if ((ray < 0.5 * M_PI) || (ray > 1.5 * M_PI))
		data->ray.right_ray = 1;
	data->ray.left_ray = !data->ray.right_ray;
}

int	check_if_wall(t_data *data, double x_cord_win, double y_cord_win)
{
	int	x_cor_in_map;
	int	y_cor_in_map;

	x_cor_in_map = floor(x_cord_win / SIZE_CUB);
	y_cor_in_map = floor(y_cord_win / SIZE_CUB);
	if (x_cor_in_map < data->nb_cls && y_cor_in_map < data->nb_rws)
		return !(data->map[y_cor_in_map][x_cor_in_map] == '0');
	// 		return (0);	
	return (0);
}

double	distance(int xplayer, int yplayer, double xpoint, double ypoint)
{
	return (sqrt(((xpoint - xplayer) * (xpoint - xplayer)) + ((ypoint - yplayer)
				* (ypoint - yplayer))));
}
