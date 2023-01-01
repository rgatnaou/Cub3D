/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 09:21:45 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/31 14:43:10 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	map_exist(char *file, int *length)
{
	int	i;

	i = 0;
	while (file[i])
	{
		while (file[i] == ' ')
			i++;
		if (file[i] == '1')
			(*length) += 1;
		else if (*length)
		{
			*length = 0;
			return ;
		}
		while (file[i] != '\n' && file[i] != '\0')
			i++;
		if (file[i] == '\n')
			i++;
	}
}

char	**get_map(char **sp_file, int length)
{
	char	**map;
	int		i;
	int		j;
	int		k;

	k = 0;
	i = 0;
	map = ft_calloc(length, sizeof(char *));
	if (!map)
		return (NULL);
	while (sp_file[i])
	{
		j = 0;
		while (sp_file[i][j] == ' ')
			j++;
		if (sp_file[i][j] == '1')
			map[k++] = ft_strdup(sp_file[i]);
		i++;
	}
	map[k] = NULL;
	return (map);
}

int	check_char_map(t_parse *parse)
{
	int	i;
	int	len;
	int	p;

	p = 0;
	if (wall(parse->data->map[0]))
		return (-1);
	i = 1;
	while (parse->data->map[i])
	{
		len = caractere_map(parse->data->map[i], &p, parse, i);
		if (len == -1)
			return (-1);
		len--;
		while (parse->data->map[i][len] == ' ')
			len--;
		if (parse->data->map[i][len] != '1')
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
			if (map[i][j] == '0' &&
				((map[i + 1] && (int)ft_strlen(map[i + 1]) <= j) || (i != 0
							&& (int)ft_strlen(map[i - 1]) <= j)))
				return (-1);
			j++;
		}
	}
	return (0);
}

int	check_map(t_parse *parse)
{
	int	length;

	length = 0;
	map_exist(parse->file, &length);
	if (length < 3)
		return (-1);
	parse->data->map = get_map(parse->sp_file, length + 1);
	if (!parse->data->map || check_char_map(parse)
		|| final_parse_map(parse->data->map))
		return (-1);
	return (0);
}
