/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:01:56 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/26 16:08:43 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <limits.h>

# define SIZE_CUB 64
# define SPEED 10
# define WIDTH 1696
# define HEIGHT 960
# define FOV (60 * (M_PI / 180))
# define WHITE 0Xffffff
# define BLUE 0X0000ff
# define RED 0Xff0000
# define MINIMAP_FACTOR 0.2

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
typedef struct s_cord
{
	double			x;
	double			y;
}				t_cord;

typedef struct s_ray
{
	bool		up;
	bool		right;
	bool		vert_hit_wall;
	bool		horz_hit_wall;
	t_cord		horz;
	t_cord		vert;
	t_cord		cast;
	double		horz_distance;
	double		vert_distance;
}				t_ray;

typedef struct s_move
{
	int	ws_move;
	int	ad_move;
	int	rotation;
}	t_move;

typedef struct s_image
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_image;

typedef struct s_mlx
{
	void		*init;
	void		*win;
	t_image		image;
}				t_mlx;


typedef struct s_player
{
	t_cord		cord;
	char		direction;
	double		rotation_angle;
}				t_player;

typedef struct s_texture
{
	unsigned int	*arr;
	int				img_width;
	int				img_height;
}	t_texture;

typedef struct s_textures
{
	t_texture	so;
	t_texture	we;
	t_texture	ea;
	t_texture	no;
}	t_textures;

typedef struct s_data
{
	char		**map;
	int			floor_color;
	int			ceiling_color;
	char		*path_no;
	char		*path_so;
	char		*path_we;
	char		*path_ea;
	int			nb_cls;
	int			nb_rws;
	int			width;
	int			height;
	t_player	player;
	t_mlx		*mlx;
	t_ray		ray;
	t_move		move;
	t_textures	texture;
}				t_data;

typedef struct s_parse
{
	char		*file;
	char		**splitted_file;
	t_data		*data;
}				t_parse;

void			free_parse(t_parse *parse);
char			*get_next_line(int fd);
void			free_tab2(char **ptr);
int				ft_error(char *msg, void *ptr);
char			*read_file(int fd);
t_data			*parse(int ac, char **av);
int				check_texture(t_parse *parse, int *t);
int				check_map(t_parse *parse);
int				wall(char *map);
int				caractere_map(char *map, int *p, t_parse *parse, int y);
int				space_map(char **map, int i, int j);
char			**get_map(char **splitted_file, int lenght);

// End Parsing

// Draw Functions:
void			my_mlx_pixel_put(t_image *data, int x, int y, int color);
int				draw(t_data *data);
int				rendering(t_data *data);
// void			circle(t_mlx *mlx, t_cord coord, int r, int color);
void			circle(t_mlx *mlx, t_cord *coord, int r, int color);
// void	circle(t_mlx *mlx, int x, int y, int r, int color);
void			square(t_mlx *mlx, int x, int y, int color);
void			line(t_data *data, double x_end, double y_end, int color);
// void			draw_player(t_data *data);
void	draw_player(t_data *data ,t_cord *start);

// Mouvements Functions:
int				key_pressed(int keycode, t_data *data);
void			draw_3d(t_data *data);

int				destroy_win(t_data *data);

// Raycasting Functions
int				check_if_wall(t_data *data, double x_cord_win, double y_cord_win);
double			limit_angle(double ray_angle);
void			check_ray_position(t_data *data, double ray);
double			distance(t_cord *point1, t_cord *point2);
double			distance_to_wall(t_data *data, double ray_angle);
void			projection(t_data *data, double ray_angle, int i);
void			move_player(t_data *data);
int				key_release(int keycode, t_data *data);
#endif
