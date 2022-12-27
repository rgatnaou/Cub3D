/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:30:04 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/27 15:39:47 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	*get_next_line(int fd)
{
	char	rd[2];
	char	*res;
	int		r_rd;

	res = malloc(1);
	if (!res)
		return (NULL);
	r_rd = 1;
	res[0] = 0;
	while (!ft_strchr(res, '\n') && r_rd)
	{
		r_rd = read(fd, rd, 1);
		if ((r_rd == -1 || !r_rd) && res[0])
			return (res);
		if (r_rd == -1 || !r_rd)
		{
			free(res);
			return (NULL);
		}
		rd[r_rd] = '\0';
		res = ft_strjoin(res, rd);
		if (rd[0] == '\n')
			break ;
	}
	return (res);
}

char	*read_file(int fd)
{
	char	*file;
	char	*line;

	file = get_next_line(fd);
	if (!file)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		file = ft_strjoin(file, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (file);
}

int	ft_error(char *msg, void *ptr)
{
	write(2, msg, ft_strlen(msg));
	if (ptr)
		free(ptr);
	return (-1);
}

t_parse	*init_parse(t_parse *parse)
{
	parse->data = malloc(sizeof(t_data));
	if (!parse->data)
	{
		free(parse);
		return (NULL);
	}
	parse->data->floor_color = 0;
	parse->data->ceiling_color = 0;
	parse->data->map = 0;
	parse->data->path_no = 0;
	parse->data->path_so = 0;
	parse->data->path_we = 0;
	parse->data->path_ea = 0;
	return (parse);
}
