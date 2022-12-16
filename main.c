/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:57:51 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/16 18:37:14 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

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
	char	**c;
	int		i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	c = ft_split(&line[i], ',');
	if (!c)
		*color = 0;
	i = 0;
	while (c[i])
	{
		*color += ft_atoi(c[i]);
		if (c[i + 1])
			*color *= 256;
		i++;
	}
	free_tab2(c);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = parse(ac, av);
	if (!data)
		return(0);
	
	data->move.ws_move = -1;
	data->move.ad_move = -1;
	data->move.rotation = -1;
	draw(data);
	return (0);
}
