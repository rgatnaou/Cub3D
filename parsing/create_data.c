/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 08:39:43 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/29 15:22:01 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	width_height(t_data *data)
{
	int	i;
	int	len;

	i = 0;
	while (data->map[i])
	{
		len = ft_strlen(data->map[i]);
		if (len > data->nb_cls)
			data->nb_cls = len;
		i++;
	}
	data->nb_rws = i;
	data->width = data->nb_cls * SIZE_CUB;
	data->height = data->nb_rws * SIZE_CUB;
}

void	init_player(t_data *data)
{
	data->map[(int)data->player.cord.y][(int)data->player.cord.x] = '0';
	data->player.cord.x = (data->player.cord.x * SIZE_CUB) + SIZE_CUB / 2;
	data->player.cord.y = (data->player.cord.y * SIZE_CUB) + SIZE_CUB / 2;
	if (data->player.direction == 'N')
		data->player.rotation_angle = 270 * M_PI / 180;
	else if (data->player.direction == 'S')
		data->player.rotation_angle = 90 * M_PI / 180;
	else if (data->player.direction == 'W')
		data->player.rotation_angle = 180 * M_PI / 180;
	else if (data->player.direction == 'E')
		data->player.rotation_angle = 0;
	data->move.ws_move = 0;
	data->move.ad_move = 0;
	data->move.rotation = 0;
	data->fov = (60 * (M_PI / 180));
	data->projection = (WIDTH / 2) / tan(data->fov / 2);
}

void	init_img(t_data *data)
{
	data->texture.no.img_ptr = check_xpm(data, data->path_no, 1);
	data->texture.so.img_ptr = check_xpm(data, data->path_so, 2);
	data->texture.we.img_ptr = check_xpm(data, data->path_we, 3);
	data->texture.ea.img_ptr = check_xpm(data, data->path_ea, 4);
	if (data->texture.no.img_ptr == NULL || data->texture.so.img_ptr == NULL
		|| data->texture.we.img_ptr == NULL || data->texture.ea.img_ptr == NULL)
	{
		printf("Error: The Texture Is Not Valid\n");
		free_data(data);
		exit(0);
	}
	check_w_h(data);
	get_addr_img(data);
}

t_data	*create_data(t_parse *parse)
{
	t_data	*data;

	data = parse->data;
	free(parse->file);
	free_tab2(parse->sp_file);
	free(parse);
	width_height(data);
	init_player(data);
	init_img(data);
	return (data);
}
