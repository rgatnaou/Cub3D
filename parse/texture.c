/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:15:57 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/02 09:50:13 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	check_tab(char *t)
{
	int	i;

	i = 0;
	while (t[i] == ' ')
		i++;
	if (t[i] == '1')
		return (0);
	write(2, "error : \"", 9);
	write(2, t, ft_strlen(t));
	return (ft_error(" \".\n", NULL));
}

int	texture(char *file, int *nb, t_elementMap *element , int txt)
{
	int	i;
	int	fd;

	i = 2;
	(*nb)++;
    if(*nb > 1)
        return (ft_error("error : texture duplicated.\n", NULL));
	if (file[i] != ' ' && file[i] != '\t' && (*nb)++)
		return (ft_error("error : texture missing separator.\n", NULL));
	while (file[i] == ' ' || file[i] == '\t' )
		i++;
	if (!file[i] && (*nb)++)
		return (ft_error("error : texture missing path.\n", NULL));
	fd = open(&file[i], O_RDWR);
	if ((fd == -1 || ft_strncmp(ft_strrchr(file, '.'), ".xpm", 4)) && (*nb)++)
		return (ft_error("error : invalid texture.\n", NULL));
	close (fd);
	if (txt == 1)
		element->no = ft_strdup(&file[i]);
	if (txt == 2)
		element->so = ft_strdup(&file[i]);
	if (txt == 3)
		element->we = ft_strdup(&file[i]);
	if (txt == 4)
		element->ew = ft_strdup(&file[i]);
	return (0);
}

int	check_color_rang(char **tex, int *nb)
{
	int	i;
	int	j;

	i = 0;
	while (tex[i])
	{
		j = 0;
		while (tex[i][j])
		{
			if (!ft_isdigit((int)tex[i][j]) && (*nb)++)
				return (ft_error("error : the color is not digit.\n", NULL));
			j++;
		}
		if (ft_atoi(tex[i]) > 255 && (*nb)++)
			return (ft_error("error : the color is out of range.\n", NULL));
		i++;
	}
	return (0);
}

int	check_color(char *file, int *nb, int *color)
{
	int		i;
	char	**tex;

	i = 1;
	(*nb)++;
	if (file[i] != ' ' && file[i] != '\t' && (*nb)++)
		return (ft_error("error : color missing separator.\n", NULL));
	while (file[i] == ' ' || file[i] == '\t' )
		i++;
	tex = ft_split(&file[i], ',');
	i = ft_strlen(file) - 1;
	if (file[i] == ',' || !tex || !tex[0] || !tex[1] || !tex[2] || tex[3])
	{
		(*nb)++;
		free_tab2(tex);
		return (ft_error("error : the color is not valid.\n", NULL));
	}
	if (!check_color_rang(tex, nb))
		*color = (ft_atoi(tex[0]) << 16) + (ft_atoi(tex[1]) << 8) + ft_atoi(tex[2]);
	free_tab2(tex);
	return (0);
}

int	check_texture(t_parse *parse, int *t)
{
	int	i;

	i = 0;
	while (parse->s_file[i])
	{
		if (!ft_strncmp(parse->s_file[i], "NO", 2))
			texture(parse->s_file[i], &t[0], parse->element, 1);
		else if (!ft_strncmp(parse->s_file[i], "SO", 2))
			texture(parse->s_file[i], &t[1], parse->element, 2);
		else if (!ft_strncmp(parse->s_file[i], "WE", 2))
			texture(parse->s_file[i], &t[2], parse->element, 3);
		else if (!ft_strncmp(parse->s_file[i], "EA", 2))
			texture(parse->s_file[i], &t[3], parse->element, 4);
		else if (!ft_strncmp(parse->s_file[i], "F", 1))
			check_color(parse->s_file[i], &t[4], &parse->element->floor);
		else if (!ft_strncmp(parse->s_file[i], "C", 1))
			check_color(parse->s_file[i], &t[5], &parse->element->ceiling);
		else if (check_tab(parse->s_file[i]))
			return (-1);
		i++;
	}
	if (t[0] == 1 && t[1] == 1 && t[2] == 1 && t[3] == 1
		&& t[4] == 1 && t[5] == 1)
		return (0);
	return (-1);
}
