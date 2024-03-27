/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:33:12 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/27 05:40:48 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include <limits.h>
# include <fcntl.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "get_next_line/get_next_line.h"

# define PI 3.141592653589793238
# define TILE_SIZE  32
# define HEIGHT  700
# define WIDTH  700
# define WALL_WIDTH 1
# define NUM_RAYS WIDTH
# define MAP_SCALE 0.2

typedef struct s_ply
{
	int		x;
	int		y;
	char	direction;
}			t_ply;

typedef struct s_player
{
	double	strafe_direction;
	double	turn_direction; // -1 if left , +1 if right , 0 nothing
	double	walk_direction; // -1 if back , +1 if front , 0 nothing
	double	rotation_angle; //
	double	movement_speed; //
	double	rotation_speed; //
	double	fov_angle;
	double	dpp;
	double	x; // x place of my player
	double	y; // y place of my player
}				t_player;

typedef struct s_map
{
	unsigned char	player_rotation_start; // 'N', 'S', 'E', 'W'
	char			**grid;
	uint32_t		f; // alloc 4 bytes for each color
	uint32_t		c; // alloc 4 bytes for each color
	int				num_cols; // number of columns
	int				num_rows; // number of rows
	int				player_x;
	int				player_y;
	int				ratiox; // dyali ana omar
	int				ratioy; //dyali ana omar
	long			map_width;
	long			map_height;
}			t_map;

typedef struct s_ray
{
	int		foundhithorizontal;
	int		foundhitvertical;
	double	wallhitxh;
	double	wallhityh;
	double	wallhitxv;
	double	wallhityv;

	double	rayangle;
	double	distance;

	double	wallhitx;
	double	wallhity;
	double	xinch;
	double	yinch;
	double	xincv;
	double	yincv;

	bool	wasvertical;

	double	israyfdown;
	double	israyfup;
	double	israyfright;
	double	israyfleft;

	double	wallstripheight;

	double	h_distance;
	double	v_distance;
}			t_ray;

typedef struct s_config
{
	t_ray		rays[NUM_RAYS];
	mlx_image_t	*img;
	t_player	player;
	mlx_t		*mlx;
	t_map		*map;
}				t_config;

typedef struct s_start
{
	int16_t			**rgb_num;
	char			*value;
	char			*key;
	int				flag;
	struct s_start	*next;
}		t_start;

// rayCasting:
uint32_t	set_color(t_ray ray);
void		initialize(t_config *config, t_map **map, mlx_t *mlx, \
mlx_image_t *img);
void		update(t_config *config);
void		hook(void *param);
void		grid(t_config *config, int tileX, int tileY, uint32_t tileColor);
void		setup_map(t_config *config);
void		setup_player(t_config *config);
void		setup_fov(t_config *config);
void		setup_wall(t_config *config);
void		cast_ray(t_config *config, int stripId, double rayangle);
void		cast_all_rays(t_config *config);
void		wall3d(t_config *config, double wallstripheight, int j, t_ray ray);
void		ceil2dfloor1d(t_config *config, int i);
void		whileforvert(t_config *config, t_ray *ray, double nvtx, \
double nvty);
void		cast_vertical_ray(t_config *config, t_ray *ray);
void		whileforhorz(t_config *config, t_ray *ray, double nextHorzTouchX, \
double nextHorzTouchY);
void		cast_horizontal_ray(t_config *config, t_ray *ray);
void		find_closest_wall_hit(t_config *config, t_ray *ray);
int			key_pressed(t_config *config);
int			is_wall(t_config *config, double x, double y);
void		update_player_pos(t_config *config);

// tools :
int			draw_line(t_config *config, double endX, double endY, \
uint32_t color);
double		distance_between_points(double x1, double y1, double x2, double y2);
double		normalize_angle(double angle);
void		*ft_malloc(size_t size);

void		ft_error(int x);
// void	Parsing();
void		raycasting(t_map *map, mlx_t *mlx, mlx_image_t *img);
t_map		*parsing(int ac, char **av);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*get_next_line(int fd);
char		**ft_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *s);
char		*ft_strtrim(char *s1, char *set);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_atoi(const char *str);
char		*ft_strtrim(char *s1, char *set);
int			check_if_exist(t_start *head, char *key);
int			list_length(t_start *head);
void		chack_spaces(char **map);
int			check_number(char *str);
int			len_char(char *str, char c);
int			help_parse_color(char *str);
int			*parse_color(t_start *head);
t_start		*create_node(char *key, char *value);
void		insert_node(t_start **head, char *key, char *value, int flag);
t_ply		*check_map_valid_char(char **map);
int			calculate_max_size_line(char **map);
char		**create_helpmap(char **map, int max_size_line, int num_rows);
char		**create_newmap(char **map, int max_size_line, int num_rows);
t_map		*valid_map(char **map);
#endif