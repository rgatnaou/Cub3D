/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_data_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:19:21 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/12/29 15:22:20 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	*check_xpm(t_data *data, char *path, int nb)
{
	if (nb == 1)
		return (mlx_xpm_file_to_image(&data->mlx, path, &data->texture.no.width,
				&data->texture.no.height));
	else if (nb == 2)
		return (mlx_xpm_file_to_image(&data->mlx, path, &data->texture.so.width,
				&data->texture.so.height));
	else if (nb == 3)
		return (mlx_xpm_file_to_image(&data->mlx, path, &data->texture.we.width,
				&data->texture.we.height));
	else
		return (mlx_xpm_file_to_image(&data->mlx, path, &data->texture.ea.width,
				&data->texture.ea.height));
}

void	get_addr_img(t_data *data)
{
	data->texture.no.arr = (unsigned int *)mlx_get_data_addr(
			data->texture.no.img_ptr,
			&data->mlx.image.bits_per_pixel,
			&data->mlx.image.line_length,
			&data->mlx.image.endian);
	data->texture.so.arr = (unsigned int *)mlx_get_data_addr(
			data->texture.so.img_ptr,
			&data->mlx.image.bits_per_pixel,
			&data->mlx.image.line_length,
			&data->mlx.image.endian);
	data->texture.we.arr = (unsigned int *)mlx_get_data_addr(
			data->texture.we.img_ptr,
			&data->mlx.image.bits_per_pixel,
			&data->mlx.image.line_length,
			&data->mlx.image.endian);
	data->texture.ea.arr = (unsigned int *)mlx_get_data_addr(
			data->texture.ea.img_ptr,
			&data->mlx.image.bits_per_pixel,
			&data->mlx.image.line_length,
			&data->mlx.image.endian);
}

void	check_w_h(t_data *data)
{
	bool	checker;

	checker = true;
	if (data->texture.so.width != 64 || data->texture.so.height != 64)
		checker = false;
	if (data->texture.no.width != 64 || data->texture.no.height != 64)
		checker = false;
	if (data->texture.we.width != 64 || data->texture.we.height != 64)
		checker = false;
	if (data->texture.ea.width != 64 || data->texture.ea.height != 64)
		checker = false;
	if (!checker)
	{
		printf("Error: The texture Size Is Not 64 * 64 Pixels\n");
		free_data(data);
		exit(1);
	}
}
