/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:53:53 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/27 18:09:29 by ykhadiri         ###   ########.fr       */
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
	data->ray.up = (ray > M_PI);
	data->ray.right = ((ray < 0.5 * M_PI) || (ray > 1.5 * M_PI));
}

int	check_if_wall(t_data *data, double x_cord_win, double y_cord_win)
{
	int	x_cor_in_map;
	int	y_cor_in_map;

	x_cor_in_map = floor(x_cord_win / SIZE_CUB);
	y_cor_in_map = floor(y_cord_win / SIZE_CUB);
	if (x_cor_in_map < data->nb_cls && y_cor_in_map < data->nb_rws)
		return (!(data->map[y_cor_in_map][x_cor_in_map] == '0'));
	return (0);
}

double	distance(t_cord *point1, t_cord *point2)
{
	return (sqrt(((point2->x - point1->x) * (point2->x - point1->x))
			+ ((point2->y - point1->y) * (point2->y - point1->y))));
}