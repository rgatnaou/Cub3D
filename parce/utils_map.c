/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:23:32 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/08/23 17:52:55 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parce.h"


int	wall(char *map)
{
	int	j;

	j = 0;
	while (map[j] && (map[j] == '1' || map[j] == ' '))
		j++;
	if (map[j])
		return (-1);
	return (0);
}

int	caractere_map(char *map, int *p)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] != '0' && map[i] != '1' && map[i] != ' ')
		{
			if (map[i] == 'N' || map[i] == 'E' || map[i] == 'S'
				|| map[i] == 'W')
				*p += 1;
			else
				return (-1);
		}
		i++;
	}
	return (i);
}

int	space_map(char **map, int i, int j)
{
	if (map[i][j] == ' ')
	{
		if (map[i + 1] && (int)ft_strlen(map[i + 1]) > j
			&& map[i + 1][j] != ' ' && map[i + 1][j] != '1')
			return (-1);
		if (map[i][j + 1] && (map[i][j + 1] != ' '
			&& map[i][j + 1] != '1'))
			return (-1);
		if (i != 0 && (int)ft_strlen(map[i - 1]) > j
			&& map[i - 1][j] != ' ' && map[i - 1][j] != '1')
			return (-1);
		if (j != 0 && map[i][j - 1] != ' ' && map[i][j - 1] != '1')
			return (-1);
	}
	return (0);
}
