/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:33:12 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/18 03:40:37 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "MLX42/include/MLX42/MLX42.h"

#define TileSize  64
#define HEIGHT  800
#define WIDTH  800

typedef struct s_player
{
	int x; // x place of my player
	int y; // y place of my player
	int Raduis;  // raduis size of my player , bcz the player is a small cercle
	int TurnDirection; // -1 if left , +1 if right , 0 nothing
	int WalkDirection; // -1 if back , +1 if front , 0 nothing
	int RotationAngle; // the player will start looking at the bottom verticaly 90 degre reverse clockwise
	int MovementSpeed; //
	int RotationSpeed; // dont be afraid the (Math.PI / 180) is to convert 3 to radian 
}			   t_player;

typedef struct s_map 
{
	char **grid;
	char *f;
	char *c;
	int Width;
	int Height;
}             t_map;

typedef struct s_config 
{
	mlx_t *mlx;
	mlx_image_t *img;
	t_player player;
	t_map	*map;
}             t_config;

int		ft_error(int x);

// void	Parsing();
void	*ft_malloc(size_t size);
int 	raycasting(t_map *map, mlx_t *mlx, mlx_image_t *img);

