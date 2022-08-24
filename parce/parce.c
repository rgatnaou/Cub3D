/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:32:50 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/08/23 18:57:42 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parce.h"

int	ft_str_cub(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		j = 0;
		while (s1[i] && s2[j] && s1[i] == s2[j])
		{
			i++;
			j++;
		}
		if (!s1[i] && !s2[j])
			return (1);
		i++;
	}
	return (0);
}

char	*file_existed(int ac, char **av)
{
	int		i;
	int		fd;
	char	*file;

	i = 0;
	if (ac != 2)
		exit (ft_error("error : give me one argument\n", NULL));
	fd = open(av[1], O_RDWR);
	if (fd == -1 || !ft_str_cub(av[1], ".cub"))
		exit (ft_error("error 404 : map not found.\n", NULL));
	file = read_file(fd);
	close(fd);
	if (!file)
		exit(ft_error("error : map is umpty.\n", NULL));
	return (file);
}

int	check_file(char *file,char **s_file)
{
	int		*t;

	t = ft_calloc(6, sizeof(int));
	if (!t)
		return (-1);
	if (check_texture(s_file, t))
	{
		free(t);
		return (ft_error("error :texture not valid.\n", NULL));
	}
	free(t);
	if (check_map(s_file, file))
		return (ft_error("error :map not valid.\n", NULL));
	return(0);
}

char	*parce(int ac, char **av)
{
	char	*file;
	char	**s_file;

	file = file_existed(ac, av);
	s_file = ft_split(file, '\n');
	if (!s_file)
	{
		free(file);
		return (NULL);
	}
	if (check_file(file, s_file))
	{
		free(file);
		free_tab2(s_file);
		return (NULL);
	}
	return(file);
}
