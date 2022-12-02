/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:30:04 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/02 13:44:13 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	*get_next_line(int fd)
{
	char		rd[2];
	char		*res;
	int			r_rd;

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
		if (rd[0] == '\n')
			break ;
		res = ft_strjoin(res, rd);
	}
	return (res);
}

char	*read_file(int fd)
{
	char	*file;
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	file = ft_strdup(line);
	file = ft_strjoin(file, "\n");
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line)
		{
			file = ft_strjoin(file, line);
			file = ft_strjoin(file, "\n");
		}
	}
	free(line);
	return (file);
}

void	free_tab2(char **ptr)
{
	int	i;

	i = 0;
	if (ptr == NULL)
		return ;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	ptr = NULL;
}

int	ft_error(char *msg, void *ptr)
{
	write(2, msg, ft_strlen(msg));
	free(ptr);
	return (-1);
}