/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:57:51 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/23 14:28:04 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	init_img_arrs(t_data *data)
{
	void	*data_tmp;

	data_tmp = mlx_xpm_file_to_image(data->mlx, data->path_ea,
			&data->texture.ea.img_width, &data->texture.ea.img_height);
	data->texture.ea.arr = (unsigned int *)mlx_get_data_addr(data_tmp,
			&data->mlx->image.bits_per_pixel, &data->mlx->image.line_length,
			&data->mlx->image.endian);
	data_tmp = mlx_xpm_file_to_image(data->mlx, data->path_we,
			&data->texture.we.img_width, &data->texture.we.img_height);
	data->texture.we.arr = (unsigned int *)mlx_get_data_addr(data_tmp,
			&data->mlx->image.bits_per_pixel, &data->mlx->image.line_length,
			&data->mlx->image.endian);
	data_tmp = mlx_xpm_file_to_image(data->mlx, data->path_so,
			&data->texture.so.img_width, &data->texture.so.img_height);
	data->texture.so.arr = (unsigned int *)mlx_get_data_addr(data_tmp,
			&data->mlx->image.bits_per_pixel, &data->mlx->image.line_length,
			&data->mlx->image.endian);
	data_tmp = mlx_xpm_file_to_image(data->mlx, data->path_no,
			&data->texture.no.img_width, &data->texture.no.img_height);
	data->texture.no.arr = (unsigned int *)mlx_get_data_addr(data_tmp,
			&data->mlx->image.bits_per_pixel, &data->mlx->image.line_length,
			&data->mlx->image.endian);
}

void	init_data(t_data *data)
{
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
	init_img_arrs(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = parse(ac, av);
	if (!data)
		return (0);
	int i = 0;
	int j;
	// while(data->map[i])
	// {
	// 	printf("cols: %zu\n",ft_strlen(data->map[i]));
	// 	i++;
	// }
	// printf("rws: %d \n",i - 1);
	// i = 0;
	// data->nb_cls = 0;
	while(data->map[i])
	{
		j = -1;
		while (data->map[i][++j]);
		if (j > data->nb_cls)
			data->nb_cls = j;
		i++;
	}
	data->nb_rws = i;
	// printf("nb cls: %d\n", data->nb_cls);
	// printf("nb rws: %d\n", data->nb_rws);
	// exit(1);
	init_data(data);
	draw(data);
	return (0);
}
