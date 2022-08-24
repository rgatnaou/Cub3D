/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:15:57 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/08/24 17:04:05 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parce.h"

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

int	texture(char *file, int *nb)
{
	int	i;
	int fd;

	i = 2;
	*nb += 1;
	if (file[i] != ' ' && file[i] != '\t')
	{
		*nb += 1;
		return (ft_error("error : texture missing separator.\n", NULL));
	}
	while (file[i] == ' ' || file[i] == '\t' )
		i++;
	if (!file[i])
	{
		*nb += 1;
		return (ft_error("error : texture missing path.\n", NULL));
	}
	fd = open(&file[i], O_RDWR);
	if (fd == -1 || !ft_str_cub(&file[i],".xpm"))
	{
	    *nb += 1;
	    return (ft_error("error : invalid texture.\n", NULL));
	}
	close (fd);
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
			if (!ft_isdigit((int)tex[i][j]))
			{
				*nb += 1;
				return (ft_error("error : the color is not digit.\n", NULL));
			}
			j++;
		}
		if (ft_atoi(tex[i]) > 255)
		{
			*nb += 1;
			return (ft_error("error : the color is out of range.\n", NULL));
		}
		i++;
	}
	return (0);
}

int	check_color(char *file, int *nb)
{
	int		i;
	char	**tex;

	i = 1;
	*nb += 1;
	if (file[i] != ' ' && file[i] != '\t')
	{
		*nb += 1;
		return (ft_error("error : color missing separator.\n", NULL));
	}
	while (file[i] == ' ' || file[i] == '\t' )
		i++;
	tex = ft_split(&file[i], ',');
	while (file[i])
		i++;
	if (file[i - 1] == ',' || !tex || !tex[0] || !tex[1] || !tex[2] || tex[3])
	{
		free_tab2(tex);
		*nb += 1;
		return (ft_error("error : the color is not digit.\n", NULL));
	}
	check_color_rang(tex, nb);
	free_tab2(tex);
	return (0);
}

int	check_texture(char **s_file, int *t)
{
	int	i;

	i = 0;
	while (s_file[i])
	{
		if (!ft_strncmp(s_file[i], "NO", 2))
			texture(s_file[i], &t[0]);
		else if (!ft_strncmp(s_file[i], "SO", 2))
			texture(s_file[i], &t[1]);
		else if (!ft_strncmp(s_file[i], "WE", 2))
			texture(s_file[i], &t[2]);
		else if (!ft_strncmp(s_file[i], "EA", 2))
			texture(s_file[i], &t[3]);
		else if (!ft_strncmp(s_file[i], "F", 1))
			check_color(s_file[i], &t[4]);
		else if (!ft_strncmp(s_file[i], "C", 1))
			check_color(s_file[i], &t[5]);
		else if (check_tab(s_file[i]))
			return (-1);
		i++;
	}
	if (t[0] == 1 && t[1] == 1 && t[2] == 1 && t[3] == 1
		&& t[4] == 1 && t[5] == 1)
		return (0);
	return (-1);
}
