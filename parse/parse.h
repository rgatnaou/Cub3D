/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:33:24 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/02 11:58:51 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>


typedef struct s_cord
{
	int	x;
	int	y;
}	t_cord;

typedef struct s_player
{
	t_cord	cord;
	char	direction;
}	t_player;

typedef struct s_elementMap
{
	char			**map;
	int				floor;
	int				ceiling;
	char			*no;
	char			*so;
	char			*we;
	char			*ew;
	t_player		*player;
}t_elementMap;

typedef struct s_parse
{
	char			*file;
	char			**s_file;
	t_elementMap	*element;
}	t_parse;

char	*get_next_line(int fd);
void	free_tab2(char **ptr);
int		ft_error(char *msg, void *ptr);
char	*read_file(int fd);
t_parse	*parse(int ac, char **av);
int		check_texture(t_parse *parse, int *t);
int		check_map(t_parse *parse);
int		wall(char *map);
int		caractere_map(char *map, int *p, t_parse *parse, int y);
int		space_map(char **map, int i, int j);
char	**get_map(char **s_file, int lenght);

#endif