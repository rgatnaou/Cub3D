/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 09:21:45 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/02 13:44:13 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	map_exist(char *file, int *nb_map, int *lenght)
{
	int	tmp_lenght;
	int	i;

	i = 0;
	tmp_lenght = 0;
	while (file[i])
	{
		while (file[i] == ' ')
			i++;
		if (file[i] == '1')
		{
			if (tmp_lenght == 0)
				(*nb_map)++;
			(*lenght)++;
			tmp_lenght++;
		}
		else if (tmp_lenght)
			tmp_lenght = 0;
		while (file[i] != '\n' && file[i] != '\0')
			i++;
		if (file[i])
			i++;
	}
}

char	**get_map(char **s_file, int lenght)
{
	char	**map;
	int		i;
	int		j;
	int		k;

	k = 0;
	i = 0;
	map = ft_calloc(lenght, sizeof(char *));
	if (!map)
		return (NULL);
	while (s_file[i])
	{
		j = 0;
		while (s_file[i][j] == ' ')
			j++;
		if (s_file[i][j] == '1')
			map[k++] = ft_strdup(s_file[i]);
		i++;
	}
	map[k] = NULL;
	return (map);
}

int	check_char_map(t_parse *parse)
{
	int	i;
	int	k;
	int	p;

	p = 0;
	if (wall(parse->data->map[0]))
		return (-1);
	i = 1;
	while (parse->data->map[i])
	{
		k = caractere_map(parse->data->map[i], &p, parse, i);
		if (k == -1)
			return (-1);
		k--;
		while (parse->data->map[i][k] == ' ')
			k--;
		if (parse->data->map[i][k] != '1')
			return (-1);
		i++;
	}
	if (wall(parse->data->map[i - 1]))
		return (-1);
	return (p - 1);
}

int	final_parse_map(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (space_map(map, i, j))
				return (-1);
			if (map[i][j] != ' ' &&
				((map[i + 1] && (int)ft_strlen(map[i + 1]) <= j)
				|| (i != 0 && j >= (int)ft_strlen(map[i - 1]))))
			{
				while (map[i][j] && map[i][j] == '1')
					j++;
				if (map[i][j])
					return (-1);
				break ;
			}
			j++;
		}
	}
	return (0);
}

int	check_map(t_parse *parse)
{
	int		nb_map;
	int		lenght;

	nb_map = 0;
	lenght = 0;
	map_exist(parse->file, &nb_map, &lenght);
	if (nb_map != 1 || lenght < 3)
		return (-1);
	parse->data->map = get_map(parse->s_file, lenght + 1);
	if (!parse->data->map || check_char_map(parse)
        || final_parse_map(parse->data->map))
		return (-1);
	return (0);
}
