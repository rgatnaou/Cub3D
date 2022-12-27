/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 08:29:06 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/27 12:40:40 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_tab2(char **ptr)
{
	int	i;

	i = 0;
	if (ptr == NULL)
		return ;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	ptr = NULL;
}

void    free_data(t_data *data)
{
    if (data)
    {
        free(data->path_no);
        free(data->path_so);
        free(data->path_we);
        free(data->path_ea);
        free_tab2(data->map);
        free(data);
    }
}

void	free_parse(t_parse *parse)
{
	if (parse)
	{
		free(parse->file);
		free_tab2(parse->splitted_file);
		free_data(parse->data);
		free(parse);
	}
}
