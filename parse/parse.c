/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:32:50 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/02 12:02:16 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_parse	*inislaze_parse(void)
{
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	if (!parse)
		return (NULL);
	parse->element = malloc(sizeof(t_elementMap));
	if (!parse->element)
		return (NULL);
	parse->element->floor = 0;
	parse->element->ceiling = 0;
	parse->element->map = 0;
	parse->element->no = 0;
	parse->element->so = 0;
	parse->element->we = 0;
	parse->element->ew = 0;
	parse->element->player = malloc(sizeof(t_player));
	if (!parse->element->player)
		return (NULL);
	return (parse);
}

void	free_parse(t_parse *parse)
{
	if (parse->element->player)
		free(parse->element->player);
	free(parse->element->no);
	free(parse->element->so);
	free(parse->element->we);
	free(parse->element->ew);
	if (parse->element)
		free(parse->element);
	if (parse)
		free(parse);
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
	if (fd == -1 || ft_strncmp(ft_strrchr(av[1], '.'), ".cub", 4))
		exit (ft_error("error 404 : map not found!\n", NULL));
	file = read_file(fd);
	close(fd);
	if (!file)
		exit(ft_error("error : map is empty.\n", NULL));
	return (file);
}

int	check_file(t_parse *parse)
{
	int		*t;

	t = ft_calloc(6, sizeof(int));
	if (!t)
		return (-1);
	if (check_texture(parse, t))
	{
		free(t);
		return (ft_error("error :texture not valid.\n", NULL));
	}
	free(t);
	if (check_map(parse))
		return (ft_error("error :map not valid.\n", NULL));
	return (0);
}

t_parse	*parse(int ac, char **av)
{
	t_parse	*parse;

	parse = inislaze_parse();
	parse->file = file_existed(ac, av);
	parse->s_file = ft_split(parse->file, '\n');
	if (!parse || !parse->file || !parse->s_file || check_file(parse))
	{
		free_parse(parse);
		return (NULL);
	}
	return (parse);
}
