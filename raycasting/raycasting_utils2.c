/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:05:51 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/31 17:32:42 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

bool	found_horz_hit_wall(t_data *data, t_cord *intercept, t_cord *step)
{
	data->ray.horz.x = 0;
	data->ray.horz.y = 0;
	while (intercept->x >= 0 && intercept->x <= data->width && intercept->y >= 0
		&& intercept->y <= data->height)
	{
		if (check_if_wall(data, intercept->x, intercept->y - data->ray.up))
		{
			data->ray.horz.x = intercept->x;
			data->ray.horz.y = intercept->y;
			data->ray.horz_distance = distance(&data->player.cord,
					&data->ray.horz);
			return (true);
		}
		else
		{
			intercept->x += step->x;
			intercept->y += step->y;
		}
	}
	data->ray.horz_distance = INT_MAX;
	return (false);
}

bool	found_vert_hit_wall(t_data *data, t_cord *intercept, t_cord *step)
{
	data->ray.vert.x = 0;
	data->ray.vert.y = 0;
	while (intercept->x >= 0 && intercept->x <= data->width && intercept->y >= 0
		&& intercept->y <= data->height)
	{
		if (check_if_wall(data, intercept->x - !data->ray.right, intercept->y))
		{
			data->ray.vert.x = intercept->x;
			data->ray.vert.y = intercept->y;
			data->ray.vert_distance = distance(&data->player.cord,
					&data->ray.vert);
			return (true);
		}
		else
		{
			intercept->x += step->x;
			intercept->y += step->y;
		}
	}
	data->ray.vert_distance = INT_MAX;
	return (false);
}

bool	horizontal_raycasting(t_data *data, double ray_angle)
{
	t_cord	intercept;
	t_cord	step;

	data->ray.horz_distance = INT_MAX;
	intercept.y = floor(data->player.cord.y / SIZE_CUB) * SIZE_CUB;
	if (!data->ray.up)
		intercept.y += SIZE_CUB;
	intercept.x = data->player.cord.x + ((intercept.y - data->player.cord.y)
			/ tan(ray_angle));
	step.y = SIZE_CUB;
	if (data->ray.up)
		step.y *= -1;
	step.x = SIZE_CUB / tan(ray_angle);
	if ((!data->ray.right && step.x > 0) || (data->ray.right && step.x < 0))
		step.x *= -1;
	return (found_horz_hit_wall(data, &intercept, &step));
}

bool	vertical_raycasting(t_data *data, double ray_angle)
{
	t_cord	intercept;
	t_cord	step;

	data->ray.vert_distance = INT_MAX;
	intercept.x = floor(data->player.cord.x / SIZE_CUB) * SIZE_CUB;
	if (data->ray.right)
		intercept.x += SIZE_CUB;
	intercept.y = data->player.cord.y + ((intercept.x - data->player.cord.x)
			* tan(ray_angle));
	step.x = SIZE_CUB;
	if (!data->ray.right)
		step.x *= -1;
	step.y = step.x * tan(ray_angle);
	if ((data->ray.up && step.y > 0) || (!data->ray.up && step.y < 0))
		step.y *= -1;
	return (found_vert_hit_wall(data, &intercept, &step));
}
