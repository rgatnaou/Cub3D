/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:32:50 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/27 12:40:46 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	*file_existed(int ac, char **av)
{
	int		i;
	int		fd;
	char	*file;

	i = 0;
	if (ac != 2)
		exit(ft_error("Error : Give Me One Argument\n", NULL));
	fd = open(av[1], O_RDWR);
	if (fd == -1 || !ft_strrchr(av[1], '.') || ft_strncmp(ft_strrchr(av[1],
				'.'), ".cub", 4))
		exit(ft_error("Error : Map Not Found!\n", NULL));
	file = read_file(fd);
	close(fd);
	if (!file)
		exit(ft_error("Error : Map Is Empty.\n", NULL));
	return (file);
}

int	check_file(t_parse *parse)
{
	int	*texture_arr;

	texture_arr = ft_calloc(6, sizeof(int));
	if (!texture_arr)
		return (-1);
	if (check_texture(parse, texture_arr))
	{
		free(texture_arr);
		return (ft_error("Error :Texture Is Not Valid.\n", NULL));
	}
	free(texture_arr);
	if (check_map(parse))
		return (ft_error("Error :Map Is Not Valid.\n", NULL));
	return (0);
}

t_data	*parse(int ac, char **av)
{
	t_parse	*parse;
	t_data	*data;

	parse = malloc(sizeof(t_parse));
	if (!parse)
		return (NULL);
	parse = init_parse(parse);
	if (!parse)
		return (NULL);
	parse->file = file_existed(ac, av);
	parse->splitted_file = ft_split(parse->file, '\n');
	if (!parse->file || !parse->splitted_file || check_file(parse))
	{
		free_parse(parse);
		return (NULL);
	}
	data = init_data(parse);
	return (data);
}
