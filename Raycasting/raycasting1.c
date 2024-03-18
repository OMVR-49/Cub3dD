/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 00:35:41 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/17 08:34:21 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void initialize(t_config *config, t_map **map)
{
	config->player.x = 0; //ps: search for x placement of the config in the array
	config->player.y = 0; //ps: search for y placement of the config in the array
	config->player.Raduis = 3;
	config->player.RotationSpeed = floor((double)(3 * (M_PI / 180)));
	config->player.TurnDirection = 0;
	config->player.WalkDirection = 0;
	config->player.RotationAngle = 0;
	config->player.MovementSpeed = 3;
	config->map = (*map);
}

void setup_map(t_config *config, mlx_t *mlx, mlx_image_t *img)
{
	int i;
	int j;
	int tileX;
	int tileY;
	int tileColor;

	i = 0;
	j = 0;
	while (i < config->map->Height)
	{
		while (j < config->map->Width)
		{
			
			tileX = j * TileSize;
			tileY = i * TileSize;
			tileColor = config->map->grid[i][j] == 1 ? 222 : 0;
			mlx_put_pixel(img, tileX, tileY, tileColor);
			j++;
		}
		i++;
	}
}

int raycasting(t_map *map, mlx_t *mlx, mlx_image_t *img)
{
	t_config *config;

	config = ft_malloc(sizeof (t_config));
	initialize(config, &map);
	setup_map(config, mlx, img);
	// player_movement();
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
