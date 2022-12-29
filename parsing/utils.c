/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:30:04 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/29 12:27:00 by rgatnaou         ###   ########.fr       */
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

int	find_caractere(char *str, char sp)
{
	int	i;
	int	s;

	i = 0;
	s = 0;
	while (str[i])
	{
		if (str[i] == sp)
			s++;
		i++;
	}
	return (s);
}
