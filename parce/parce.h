/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:33:24 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/11/30 12:12:42 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCE_H
# define PARCE_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct s_color
{
    char red[3];
    char green[3];
    char blue[3];
} t_color;

typedef struct s_cord
{
    float x;
    float y;
} t_cord;

typedef struct s_player
{
    struct s_cord xy;
    char direction[2];
    
} t_player;

typedef struct s_elementMap
{
    char **map;
    struct s_color *floor;
    struct s_color *ceiling;
    char *NO;
    char *SO;
    char *WE;
    char *EA;
    struct s_player player;
}t_elementMap;

typedef struct s_parce
{
    char *file;
    char **s_file;
    struct s_elementMap *element;
    int bool;
} t_parce;



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