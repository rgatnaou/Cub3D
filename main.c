/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:57:51 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/16 19:19:46 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	init_data(t_data *data)
{
	data->map[data->player.cord.y][data->player.cord.x] = '0';
	data->player.cord.x = (data->player.cord.x * SIZE_CUB) + 10;
	data->player.cord.y = (data->player.cord.y * SIZE_CUB) + 10;
	if (data->player.direction == 'N')
		data->player.rotation_angle = 270 * M_PI / 180;
	else if (data->player.direction == 'S')
		data->player.rotation_angle = M_PI / 2;
	else if (data->player.direction == 'W')
		data->player.rotation_angle = M_PI;
	else if (data->player.direction == 'E')
		data->player.rotation_angle = 0;
	data->move.ws_move = -1;
	data->move.ad_move = -1;
	data->move.rotation = -1;
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = parse(ac, av);
	if (!data)
		return (0);
	init_data(data);
	draw(data);
	return (0);
}
