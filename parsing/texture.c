/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:15:57 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/02 20:30:24 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_sp_map(char *splitted_file)
{
	int	i;

	i = 0;
	while (splitted_file[i] == ' ')
		i++;
	if (splitted_file[i] == '\t')
	{
		while (splitted_file[i] == ' ' || splitted_file[i] == '\t')
			i++;
		if (!splitted_file[i])
			return (0);
		else
		{
			write(2, "Error : \"", 9);
			write(2, splitted_file, ft_strlen(splitted_file));
			return (ft_error(" \".\n", NULL));
		}
	}
	if (splitted_file[i] == '1' || !splitted_file[i])
		return (0);
	write(2, "Error : \"", 9);
	write(2, splitted_file, ft_strlen(splitted_file));
	return (ft_error(" \".\n", NULL));
}

int	texture_errors(char *line, int *text_val, t_data *data , char orientation)
{
	int	i;
	int	fd;

	i = 2;
	(*text_val)++;
    if(*text_val > 1)
        return (ft_error("Error :Texture Duplicated.\n", NULL));
	if (line[i] != ' ' && line[i] != '\t' && (*text_val)++)
		return (ft_error("Error :Texture Missing Separator.\n", NULL));
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (!line[i] && (*text_val)++)
		return (ft_error("Error :Texture Missing Path.\n", NULL));
	fd = open(&line[i], O_RDWR);
	if ((fd == -1 || !ft_strrchr(line, '.') || ft_strncmp(ft_strrchr(line, '.'), ".xpm", 4)) && (*text_val)++)
		return (ft_error("Error :Invalid Texture Path.\n", NULL));
	close (fd);
	if (orientation == 'N')
		data->no = ft_strdup(&line[i]);
	if (orientation == 'S')
		data->so = ft_strdup(&line[i]);
	if (orientation == 'W')
		data->we = ft_strdup(&line[i]);
	if (orientation == 'E')
		data->ea = ft_strdup(&line[i]);
	return (0);
}

int	check_color_rang(char **sp_color, int *text_val)
{
	int	i;
	int	j;

	i = 0;
	while (sp_color[i])
	{
		j = 0;
		while (sp_color[i][j])
		{
			if (!ft_isdigit((int)sp_color[i][j]) && (*text_val)++)
				return (ft_error("Error :The Color Is Not Digit.\n", NULL));
			j++;
		}
		if (ft_atoi(sp_color[i]) > 255 && (*text_val)++)
			return (ft_error("Error :The Color Is Out Of Range.\n", NULL));
		i++;
	}
	return (0);
}

int	check_color(char *line, int *text_val, int *color)
{
	int		i;
	char	**sp_color;

	i = 1;
	(*text_val)++;
	if(*text_val > 1)
        return (ft_error("Error :Color Duplicated.\n", NULL));
	if (line[i] != ' ' && line[i] != '\t' && (*text_val)++)
		return (ft_error("Error :Color Missing Separator.\n", NULL));
	while (line[i] == ' ' || line[i] == '\t' )
		i++;
	sp_color = ft_split(&line[i], ',');
	i = ft_strlen(line) - 1;
	if (line[i] == ',' || !sp_color || !sp_color[0] || !sp_color[1] || !sp_color[2] || sp_color[3])
	{
		(*text_val)++;
		free_tab2(sp_color);
		return (ft_error("Error :The Color Is Not Valid.\n", NULL));
	}
	if (!check_color_rang(sp_color, text_val))
		*color = (ft_atoi(sp_color[0]) << 16) + (ft_atoi(sp_color[1]) << 8) + ft_atoi(sp_color[2]);
	free_tab2(sp_color);
	return (0);
}

int	check_texture(t_parse *parse, int *texture_arr)
{
	int	i;

	i = 0;
	while (parse->splitted_file[i])
	{
		if (!ft_strncmp(parse->splitted_file[i], "NO", 2))
			texture_errors(parse->splitted_file[i], &texture_arr[0], parse->data, 'N');
		else if (!ft_strncmp(parse->splitted_file[i], "SO", 2))
			texture_errors(parse->splitted_file[i], &texture_arr[1], parse->data, 'S');
		else if (!ft_strncmp(parse->splitted_file[i], "WE", 2))
			texture_errors(parse->splitted_file[i], &texture_arr[2], parse->data, 'W');
		else if (!ft_strncmp(parse->splitted_file[i], "EA", 2))
			texture_errors(parse->splitted_file[i], &texture_arr[3], parse->data, 'E');
		else if (!ft_strncmp(parse->splitted_file[i], "F", 1))
			check_color(parse->splitted_file[i], &texture_arr[4], &parse->data->floor_color);
		else if (!ft_strncmp(parse->splitted_file[i], "C", 1))
			check_color(parse->splitted_file[i], &texture_arr[5], &parse->data->ceiling_color);
		else if (check_sp_map(parse->splitted_file[i]))
			return (-1);
		i++;
	}
	if (texture_arr[0] == 1 && texture_arr[1] == 1 && texture_arr[2] == 1 && texture_arr[3] == 1
		&& texture_arr[4] == 1 && texture_arr[5] == 1)
		return (0);
	return (-1);
}
