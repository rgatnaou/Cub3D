/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:01:56 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/12/15 19:20:58 by ykhadiri         ###   ########.fr       */
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

# define SIZE_CUB 32
# define NB_CLS 53
# define NB_RWS 30
# define SPEED 7
# define WIDTH (NB_CLS * SIZE_CUB)
# define HEIGHT (NB_RWS * SIZE_CUB)
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

typedef struct s_ray
{
	bool		up_ray;
	bool		right_ray;
	bool		down_ray;
	bool		left_ray;
	bool		vert_hit_wall;
	bool		horz_hit_wall;
	double		xfinal_horz_coord;
	double		yfinal_horz_coord;
	double		xfinal_vert_coord;
	double		yfinal_vert_coord;
	double		horz_distance;
	double		vert_distance;
	double		xpoint;
	double		ypoint;

}				t_ray;

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

typedef struct s_cord
{
	int			x;
	int			y;
}				t_cord;

typedef struct s_player
{
	t_cord		cord;
	char		direction;
	double		rotation_angle;
}				t_player;

typedef struct s_data
{
	char		**map;
	int			floor_color;
	int			ceiling_color;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	t_player	player;
	t_mlx		*mlx;
	t_ray		ray;
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
t_parse			*parse(int ac, char **av);
int				check_texture(t_parse *parse, int *t);
int				check_map(t_parse *parse);
int				wall(char *map);
int				caractere_map(char *map, int *p, t_parse *parse, int y);
int				space_map(char **map, int i, int j);
char			**get_map(char **splitted_file, int lenght);

// End Parsing

// Draw Functions:
void			my_mlx_pixel_put(t_image *data, int x, int y, int color);
int				draw(t_parse *parsing);
void			draw_2d_map(t_data *data);
void			circle(t_mlx *mlx, int x, int y, int r, int color);
void			square(t_mlx *mlx, int x, int y, int color);
void			line(t_data *data, double x_end, double y_end, int color);
void			raycasting(t_data *data);

// Mouvements Functions:
int				move_player(int keycode, t_parse *parse);
void			draw_in_3d(t_data *data);

int				destroy_win(t_parse *parsing);

// Raycasting Functions
int				check_if_wall(t_data *data, int x_cord_win, int y_cord_win);
double			limit_angle(double ray_angle);
void			check_ray_position(t_data *data, double ray);
double			distance(int xplayer, int yplayer, double xpoint,
					double ypoint);
double			distance_to_wall(t_data *data, double ray_angle);
void	projection(t_data *data, double ray_angle, int i);
#endif
