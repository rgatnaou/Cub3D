/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:57:51 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/08/24 18:51:01 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*initialize_texture(char *line)
{
	int	i;

	i = 0;
	// while (line[i] == ' ' || line[i] == '\t')
	// 	i++;
	// *fd = open(&line[i], O_RDWR);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (0);
}

void	initialize_color(char *line, int *color)
{
	char **c;
	int i;
	
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	c = ft_split(&line[i], ',');
	if (!c)
		*color = 0;
	i = 0;
	while(c[i])
	{
		*color += ft_atoi(c[i]);
		if (c[i + 1])
			*color *= 256;
		i++;
	}
	free_tab2(c);
}

void get_texture(t_data *m,char **s_file, int *l)
{
	int i;
	i = 0;
	while (s_file[i])
	{
		if (!ft_strncmp(s_file[i], "NO", 2))
			m->tex[0] = initialize_texture(&s_file[i][2]);
		else if (!ft_strncmp(s_file[i], "SO", 2))
			m->tex[1] =initialize_texture(&s_file[i][2]);
		else if (!ft_strncmp(s_file[i], "WE", 2))
			m->tex[2] = initialize_texture(&s_file[i][2]);
		else if (!ft_strncmp(s_file[i], "EA", 2))
			m->tex[3] = initialize_texture(&s_file[i][2]);
		else if (!ft_strncmp(s_file[i], "F", 1))
			initialize_color(&s_file[i][1], &m->color[0]);
		else if (!ft_strncmp(s_file[i], "C", 1))
			initialize_color(&s_file[i][1], &m->color[1]);
		else if (ft_strchr(s_file[i], '1'))
			*l += 1;
		i++;
	}
}

void inistize_data(t_data *m,char *file)
{
	int		l;
	char	**s_file;

	s_file = ft_split(file, '\n');
	if (!s_file)
		return ;
	l = 0;
	get_texture(m, s_file, &l);
	if (l == 0)
	{
		free_tab2(s_file);
		return ;
	}
	m->map = get_map(s_file, l + 1);
	if (!m->map)
	{
		free_tab2(s_file);
		return ;
	}
	m->mlx = mlx_init();
	m->win = mlx_new_window(m->mlx, 1920, 1080, "Hello world!");
	free_tab2(s_file);
}

int	main(int ac, char **av)
{
	char *file;
	t_data *m;

	m = malloc(sizeof(t_data));
	file = parce(ac, av);
	if (!file)
		return(-1);
	inistize_data(m, file);
	draw(m);
	return (0);
}
