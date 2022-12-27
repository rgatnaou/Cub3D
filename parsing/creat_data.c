/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 08:39:43 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/27 13:46:48 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void width_height(t_data *data)
{
    int i;
    int len;

    i = 0;
    while(data->map[i])
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

void    init_player(t_data *data)
{
    data->map[(int)data->player.cord.y][(int)data->player.cord.x] = '0';
	data->player.cord.x = (data->player.cord.x * SIZE_CUB) + SIZE_CUB / 2;
	data->player.cord.y = (data->player.cord.y * SIZE_CUB) + SIZE_CUB / 2;
	if (data->player.direction == 'N')
		data->player.rotation_angle = 270 * M_PI / 180;
	else if (data->player.direction == 'S')
		data->player.rotation_angle = 90 * M_PI / 180;
	else if (data->player.direction == 'W')
		data->player.rotation_angle =  180 * M_PI / 180;
	else if (data->player.direction == 'E')
		data->player.rotation_angle = 0;
	data->move.ws_move = 0;
	data->move.ad_move = 0;
	data->move.rotation = 0;
	data->projection = (WIDTH / 2) / tan(FOV / 2);
}
void *check_xpm(t_data *data,char *path,int nb)
{
    if (nb == 1)
        return(mlx_xpm_file_to_image(&data->mlx, path,
            &data->texture.no.width, &data->texture.no.height));
    else if (nb == 2)
        return(mlx_xpm_file_to_image(&data->mlx, path,
            &data->texture.so.width, &data->texture.so.height));
    else if (nb == 3)
        return(mlx_xpm_file_to_image(&data->mlx, path,
            &data->texture.we.width, &data->texture.we.height));
    else
        return(mlx_xpm_file_to_image(&data->mlx, path,
            &data->texture.ea.width, &data->texture.ea.height));
}

void get_addr_img(t_data *data, void *img_no, void *img_so, void *img_we, void *img_ea)
{
    data->texture.no.arr = (unsigned int *)mlx_get_data_addr(img_no,
            &data->mlx.image.bits_per_pixel, &data->mlx.image.line_length,
            &data->mlx.image.endian);
    data->texture.so.arr = (unsigned int *)mlx_get_data_addr(img_so,
            &data->mlx.image.bits_per_pixel, &data->mlx.image.line_length,
            &data->mlx.image.endian);
    data->texture.we.arr = (unsigned int *)mlx_get_data_addr(img_we,
            &data->mlx.image.bits_per_pixel, &data->mlx.image.line_length,
            &data->mlx.image.endian);
    data->texture.ea.arr = (unsigned int *)mlx_get_data_addr(img_ea,
			&data->mlx.image.bits_per_pixel, &data->mlx.image.line_length,
			&data->mlx.image.endian);
    
}
void    init_img(t_data *data)
{
    void *img_no;
    void *img_so;
    void *img_we;
    void *img_ea;
    
    img_no = check_xpm(data, data->path_no, 1);
        
    img_so = check_xpm(data, data->path_so, 2);
    
    img_we = check_xpm(data, data->path_we, 3);
    
    img_ea = check_xpm(data, data->path_ea, 4);
    
        printf("data\n");
    if (img_no == NULL || img_so == NULL || img_we == NULL || img_ea == NULL)
    {
        free_data(data);
        free(img_no);
        free(img_so);
        free(img_we);
        free(img_ea);
        exit(0);
    }
    get_addr_img(data, img_no, img_so, img_we, img_ea);
}

t_data	*init_data(t_parse *parse)
{
	t_data	*data;

	data = parse->data;
	free(parse->file);
	free_tab2(parse->splitted_file);
	free(parse);
    width_height(data);
    init_player(data);
    init_img(data);

    return(data);
}