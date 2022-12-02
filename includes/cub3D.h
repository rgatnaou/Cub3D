/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:01:56 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/02 15:20:34 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>


# define WIDTH 1024
# define HEIGHT 800
# define WHITE 0Xffffff
# define BLUE 0X0000ff

# define KEY_W 13
# define KEY_D 2
# define KEY_A 0
# define KEY_S 1
# define KEY_ESC 53
# define PI 3.14159265359

// Begin Parsing:
typedef struct	s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct s_mlx {
	void	*mlx;
	void	*win;
	t_image	image;
}	t_mlx;

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

typedef struct s_data
{
	char			**map;
	int				floor_color;
	int				ceiling_color;
	char			*no;
	char			*so;
	char			*we;
	char			*ew;
	t_player		player;
	t_mlx			*mlx;
}	t_data;

typedef struct s_parse
{
	char			*file;
	char			**s_file;
	t_data			*data;
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

// End Parsing

// Draw Functions:
int draw(t_data *data);

#endif
