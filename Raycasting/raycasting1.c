/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 00:35:41 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/22 03:18:51 by sacharai         ###   ########.fr       */
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
	config->player.x = (*map)->playerX;
	config->player.y = (*map)->playerY;
}

void grid(mlx_image_t *img, int tileX , int tileY, uint32_t tileColor)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < TileSize)
	{
		y = 0;
		while(y < TileSize) 
		{
			mlx_put_pixel(img, y + tileX, x + tileY, tileColor);
			y++;
		}
		x++;
	}
}

void setup_map(t_config *config, mlx_t *mlx, mlx_image_t *img)
{
	uint32_t tileColor;
	int i;
	int j;
	int x;
	int y;

	i = 0;
	y = 0;
	while (y < config->map->num_rows)
	{
		j = 0;
		x = 0;
		while (x < config->map->num_cols)
		{
			if(config->map->grid[y][x] == 1)
				tileColor = 0x00008BFF;
			else
				tileColor = 0xFFFFFFFF;
			grid(img, i, j, tileColor);
			j += TileSize;
			x++;
		}
		i += TileSize;
		y++;
	}
	mlx_image_to_window(mlx, img, 0, 0);
}

void	setup_player(t_config *config, mlx_t *mlx, mlx_image_t *img)
{
	// int x;
	// int y;
	
	// // x = (config->player.x * TileSize) + (TileSize / 2);
	// // y = (config->player.y * TileSize) + (TileSize / 2);
	// mlx_put_pixel(img, x, y ,0xFF2E2EFF);
	// while((x + (cos(config->player.RotationAngle) * 20)) < TileSize)
	// {
	// 	y = 0;
	// 	while((y + ((cos(config->player.RotationAngle) * 20))) < TileSize )
	// 	{
	// 		mlx_put_pixel(img, x, y ,0xFF2E2EFF);
	// 		y++;
	// 	}
	// 	x++;
	// }

}

void	keyPressed(void *param) // if necessery typecast the void parameter u understand
{
	mlx_key_data_t keyCode;
	t_config *config;

	config = (struct s_config *)param;
	if (keyCode.key == MLX_KEY_UP && keyCode.action == MLX_PRESS)
		config->player.WalkDirection = 1;
	if (keyCode.key == MLX_KEY_UP && keyCode.action == MLX_RELEASE)
		config->player.WalkDirection = 0;
	if (keyCode.key == MLX_KEY_DOWN && keyCode.action == MLX_PRESS)
		config->player.WalkDirection = -1;
	if (keyCode.key == MLX_KEY_DOWN && keyCode.action == MLX_RELEASE)
		config->player.WalkDirection = 0;
	if (keyCode.key == MLX_KEY_RIGHT && keyCode.action == MLX_PRESS)
		config->player.TurnDirection = 1;
	if (keyCode.key == MLX_KEY_RIGHT && keyCode.action == MLX_RELEASE)
		config->player.TurnDirection = 0;
	if (keyCode.key == MLX_KEY_LEFT && keyCode.action == MLX_PRESS)
		config->player.TurnDirection = -1;
	if (keyCode.key == MLX_KEY_LEFT && keyCode.action == MLX_RELEASE)
		config->player.TurnDirection = 0;
}

void	player_movement(t_config *config, mlx_t *mlx, mlx_image_t *img)
{
	mlx_key_data_t keys;

	setup_player(config, mlx, img);
	mlx_loop_hook(mlx, &keyPressed, config);
}

int raycasting(t_map *map, mlx_t *mlx, mlx_image_t *img)
{
	t_config *config;

	config = ft_malloc(sizeof (t_config));
	initialize(config, &map);
	setup_map(config, mlx, img);
	player_movement(config, mlx, img);
	return (EXIT_SUCCESS);
}
