/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 09:21:45 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/08/22 20:00:22 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parce.h"

void	map_exist(char *file, int *nb_map, int *lenght)
{
	int	tmp_lenght;
	int	i;

	i = 0;
	tmp_lenght = 0;
	while (file[i])
	{
		while ((file[i] == ' ' || file[i] == '\t'))
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

char **get_map(char **s_file,int lenght)
{
	char **map;
	int i;
	int j;
	int k;

	k = 0;
	i = 0;
	map = ft_calloc(lenght, sizeof(char *));
	if (!map)
		return(NULL);
	while(s_file[i])
	{
		j = 0;
		while (s_file[i][j] == ' ' || s_file[i][j] == '\t')
			j++;
		if (s_file[i][j] == '1')
		{
			map[k++] = ft_strdup(s_file[i]);
			if (!map[k - 1])
				return(NULL);
		}
		i++;
	}
	map[k] = NULL;
	return(map);
}

int check_char_map(char **map)
{
	int i;
	int j;
	int k;
	int p;
	
	i = 0;
	p = 0;
	while(map[0][i] && (map[0][i] == '1' || map[0][i] == ' '))
		i++;
	if (map[0][i])
		return (-1);
	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' '
				&& map[i][j] != '\t')
			{
				if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'S'
				|| map[i][j] == 'W')
					p++;
				else
					return (-1);
			}
			j++;
		}
		k = j - 1;
		while (map[i][k] == ' ')
			k--;
		if (map[i][k] != '1')
			return (-1);
		i++;
	}
	j = 0;
	while(map[i - 1][j] && (map[i - 1][j] == '1' || map[i - 1][j] == ' '))
		j++;
	if (map[i - 1][j])
		return (-1);
	return (p - 1);
}

int final_parse_map(char **map)
{
	int i;
	int j;
	int k;

	i = 0;
	while(map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
			{
				if (map[i + 1] && (int)ft_strlen(map[i + 1]) > j && map[i + 1][j] != ' ' && map[i + 1][j] != '1')
					return (-1);
				if (map[i][j + 1] && (map[i][j + 1] != ' ' && map[i][j + 1] != '1'))
					return (-1);
				if (i != 0 && (int)ft_strlen(map[i - 1]) > j && map[i - 1][j] != ' ' && map[i - 1][j] != '1')
					return (-1);
				if (j != 0 && map[i][j - 1] != ' ' && map[i][j - 1] != '1')
					return(-1);
			}
			// else if (map[i + 1] && (int)ft_strlen(map[i + 1]) > j)
			// {
				
			// }
			else if (i != 0 && ft_strlen(map[i - 1]) < ft_strlen(map[i]) && j + 1 >= (int)ft_strlen(map[i - 1]))
			{
				printf("%s\n",map[i]);
				k = j;
				while(map[i][j] && (map[i][j] == ' ' || map[i][j] == '1'))
					j++;
				// if (map[i][j])
				// {
				// 	printf("%s\n",map[i]);
				// 	return(-1);
				// }
				j = k;
			}
			j++;
		}
		i++;
	}
	return (0);
}

int parse_map(char **map)
{
	if (check_char_map(map))
		return(-1);
	if (final_parse_map(map))
		return(-1);
	return(0);
	
}
int check_map(char **s_file, char *file)
{
	char **map;
	int	nb_map;
	int	lenght;
    
	nb_map = 0;
	lenght = 0;
	map_exist(file,&nb_map,&lenght);
	if (nb_map != 1 || lenght < 3)
		return (-1);
	map = get_map(s_file, lenght);
	if (!map || parse_map(map))
		return(-1);
	return(0);
}