/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:33:12 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/26 10:07:32 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#include <fcntl.h>
#include "MLX42/include/MLX42/MLX42.h"
#include "get_next_line/get_next_line.h"

#define Pi 3.141592653589793238
#define TileSize  32
#define HEIGHT  700
#define WIDTH  700
#define FOV_ANGLE  (60 * (M_PI / 180))
#define Wall_Width 1
#define NUM_RAYS (WIDTH / Wall_Width)
#define MAP_Scale 0.2
#define dPP ((WIDTH / 2) / tan(FOV_ANGLE / 2))

typedef struct s_ply
{
	int x;
	int y;
	char direction;
} t_ply;
typedef struct s_player
{
	double x; // x place of my player
	double y; // y place of my player
	int Raduis;  // raduis size of my player , bcz the player is a small cercle
	double TurnDirection; // -1 if left , +1 if right , 0 nothing
	double WalkDirection; // -1 if back , +1 if front , 0 nothing
	double RotationAngle; // the player will start looking at the bottom verticaly 90 degre reverse clockwise
	double MovementSpeed; //
	double StrafeDirection;
	double RotationSpeed; // dont be afraid the (Math.PI / 180) is to convert 3 to radian 
}			   t_player;

typedef struct s_map 
{
	char **grid;
	int f; // alloc 4 bytes for each color
	int c; // alloc 4 bytes for each color
	unsigned char PlayerRotationStart; // 'N', 'S', 'E', 'W'
	int num_cols; // number of columns
	int num_rows; // number of rows
	int playerX;
	int playerY;
	double ratioX; // dyali ana omar
	double ratioY; //dyali ana omar
}             t_map;

typedef struct s_ray {
    double rayAngle;
    double distance;

    double wallHitX;
    double wallHitY;
    double wallHitXH;
    double wallHitYH;
    double wallHitXV;
    double wallHitYV;
	double XincH;
	double YincH;
	double XincV;
	double YincV;

    int foundHitVertical;
    int foundHitHorizontal;
	bool wasvertical;

	double isRayFacingDown;
	double isRayFacingUp;
	double isRayFacingRight;
	double isRayFacingLeft;

	double wallStripHeight;
} t_ray;

typedef struct s_config 
{
	mlx_image_t	*img;
	t_player	player;
	mlx_t		*mlx;
	t_map		*map;
	t_ray rays[NUM_RAYS];
}             t_config;

typedef struct s_start
{
	int16_t **rgb_num;
	char *key;
	char *value;
	int flag;
	struct s_start *next;
} 			t_start;

// rayCasting:
void	initialize(t_config *config, t_map **map, mlx_t *mlx, mlx_image_t *img);
void	Update(t_config *config);
void	Hook(void *param);
void	grid(t_config *config, int tileX , int tileY, uint32_t tileColor);
void	setup_map(t_config *config);
void	setup_player(t_config *config);
void	setup_fov(t_config *config);
void	setup_wall(t_config *config);
void	castRay(t_config *config, int stripId, double rayAngle);
void 	castAllRays(t_config *config);
uint32_t	set_color(t_ray ray);
void 	wall3D(t_config *config, double wallStripHeight, int j, t_ray ray);
void	ceil2DFloor1D(t_config *config, int i);
void 	whileForVert(t_config *config, t_ray *ray, double nextVertTouchX, double nextVertTouchY);
void	castVerticalRay(t_config *config, t_ray *ray);
void	whileForHorz(t_config *config, t_ray *ray, double nextHorzTouchX, double nextHorzTouchY);
void	castHorizontalRay(t_config *config, t_ray *ray);
void	findClosestWallHit(t_config *config, t_ray *ray);
int		KeyPressed(t_config *config);
int		isWall(t_config *config, double x, double y);
void	UpdatePlayerPos(t_config *config);
// tools :
int 	draw_line(t_config *config, double endX, double endY, uint32_t color);
void	*ft_malloc(size_t size);
double	distanceBetweenPoints(double x1, double y1, double x2, double y2);
double	normalizeAngle(double angle);


int		ft_error(int x);
// void	Parsing();
void 	raycasting(t_map *map, mlx_t *mlx, mlx_image_t *img);
t_map	*parsing(int ac, char **av);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_next_line(int fd);
char    **ft_split(char const *s, char c);
char    *ft_substr(char const *s, unsigned int start, size_t len);
char    *ft_strdup(const char *s);
char    *ft_strtrim(char *s1, char *set);
int     ft_strcmp(const char *s1, const char *s2);
int	 	ft_atoi(const char *str);