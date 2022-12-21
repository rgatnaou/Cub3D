/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:57:51 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/20 17:15:23 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	init_data(t_data *data)
{
	void *data_tmp;

	data->map[(int)data->player.cord.y][(int)data->player.cord.x] = '0';
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

	data_tmp = mlx_xpm_file_to_image(data->mlx, data->path_ea, &data->texture.img_width, &data->texture.img_height);
	data->texture.ea = (unsigned int *)mlx_get_data_addr(data_tmp, &data->mlx->image.bits_per_pixel, &data->mlx->image.line_length, &data->mlx->image.endian);

	data_tmp = mlx_xpm_file_to_image(data->mlx, data->path_we, &data->texture.img_width, &data->texture.img_height);
	data->texture.we = (unsigned int *)mlx_get_data_addr(data_tmp, &data->mlx->image.bits_per_pixel, &data->mlx->image.line_length, &data->mlx->image.endian);

	data_tmp = mlx_xpm_file_to_image(data->mlx, data->path_so, &data->texture.img_width, &data->texture.img_height);
	data->texture.so = (unsigned int *)mlx_get_data_addr(data_tmp, &data->mlx->image.bits_per_pixel, &data->mlx->image.line_length, &data->mlx->image.endian);

	data_tmp = mlx_xpm_file_to_image(data->mlx, data->path_no, &data->texture.img_width, &data->texture.img_height);
	data->texture.no = (unsigned int *)mlx_get_data_addr(data_tmp, &data->mlx->image.bits_per_pixel, &data->mlx->image.line_length, &data->mlx->image.endian);
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
