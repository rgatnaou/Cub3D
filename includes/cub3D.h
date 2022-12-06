/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:01:56 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/06 13:14:51 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>

# define SIZE_CUB 30
# define NB_CLS 53
# define NB_RWS 30
# define SPEED 5
# define WIDTH (NB_CLS * SIZE_CUB)
# define HEIGHT (NB_RWS * SIZE_CUB)
# define FOV (60 * (M_PI / 180))
# define WHITE 0Xffffff
# define BLUE 0X0000ff
# define RED 0Xff0000

# define KEY_W 13
# define KEY_D 2
# define KEY_A 0
# define KEY_S 1
# define KEY_ARROW_TOP 126
# define KEY_ARROW_RIGHT 124
# define KEY_ARROW_DOWN 125
# define KEY_ARROW_LEFT 123
# define KEY_S 1
# define KEY_ESC 53

// Begin Parsing:
typedef struct	s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct s_mlx {
	void	*init;
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
	double	rotation_angle;
}	t_player;

typedef struct s_data
{
	char			**map;
	int				floor_color;
	int				ceiling_color;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	t_player		player;
	t_mlx			*mlx;
}	t_data;

typedef struct s_parse
{
	char			*file;
	char			**splitted_file;
	t_data			*data;
}	t_parse;

void	free_parse(t_parse *parse);
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
char	**get_map(char **splitted_file, int lenght);

// End Parsing

// Draw Functions:
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);
int		draw(t_parse *parsing);
void	draw_2d_map(t_data *data);
void	circle(t_mlx *mlx, int x, int y, int r, int color);
void	square(t_mlx *mlx, int x, int y, int color);
void	line(t_data *data, int x_end, int y_end, int color);
void	draw_player(t_data *data);

// Mouvements Functions:
int		move_player(int keycode, t_parse *parse);
void	raycasting(t_data *data);

int	destroy_win(t_parse *parsing);
#endif
