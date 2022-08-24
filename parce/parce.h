/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:33:24 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/08/23 19:50:34 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCE_H
# define PARCE_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>

char	*get_next_line(int fd);
void	free_tab2(char **ptr);
int		ft_error(char *msg, void *ptr);
char	*read_file(int fd);
int		ft_str_cub(char *s1, char *s2);
char	*parce(int ac, char **av);
int		check_texture(char **file, int *t);
int		check_map(char **s_file, char *file);
int		wall(char *map);
int		caractere_map(char *map, int *p);
int		space_map(char **map, int i, int j);
char	**get_map(char **s_file, int lenght);

#endif