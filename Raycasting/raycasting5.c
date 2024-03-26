/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:58:59 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/26 10:06:49 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	KeyPressed(t_config *config)
{
	int i;

	i = 0;
	if (mlx_is_key_down(config->mlx, MLX_KEY_S))
		config->player.WalkDirection = -1 + (0 * i++);
	if (mlx_is_key_down(config->mlx, MLX_KEY_W))
		config->player.WalkDirection = 1 + (0 * i++);
	if (mlx_is_key_down(config->mlx, MLX_KEY_RIGHT))
		config->player.TurnDirection = 1 + (0 * i++);
	if (mlx_is_key_down(config->mlx, MLX_KEY_LEFT))
		config->player.TurnDirection = -1 + (0 * i++);
	if (mlx_is_key_down(config->mlx, MLX_KEY_D))
		config->player.StrafeDirection = 1 + (0 * i++);
	if (mlx_is_key_down(config->mlx, MLX_KEY_A))
		config->player.StrafeDirection = -1 + (0 * i++);
	if (mlx_is_key_down(config->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(config->mlx);
	return(i);
}

int isWall(t_config *config, double x, double y)
{
	int mapGridIndexX;
	int mapGridIndexY;

	if (x <= 0 || x >= WIDTH || y <= 0 || y >= HEIGHT)
		return (1);
	mapGridIndexX = floor(x / (config->map->ratioX));
	mapGridIndexY = floor(y / (config->map->ratioY));
	if (mapGridIndexX < 0 || mapGridIndexX >= config->map->num_cols || mapGridIndexY < 0 || mapGridIndexY >= config->map->num_rows)
		return (1);
	if (config->map->grid[mapGridIndexY][mapGridIndexX] == '1')
		return (1);
	return (0);
}

void UpdatePlayerPos(t_config *config)
{
	double moveStep;
	double newPlayerX;
	double newPlayerY;
	double strafeStep;

	config->player.RotationAngle += config->player.TurnDirection * config->player.RotationSpeed;
	moveStep = config->player.WalkDirection * config->player.MovementSpeed;
	newPlayerX = config->player.x + cos(config->player.RotationAngle) * moveStep;
	newPlayerY = config->player.y + sin(config->player.RotationAngle) * moveStep;
	strafeStep = config->player.StrafeDirection * config->player.MovementSpeed;
	newPlayerX += cos(config->player.RotationAngle + M_PI_2) * strafeStep;
	newPlayerY += sin(config->player.RotationAngle + M_PI_2) * strafeStep;
	if (!isWall(config, newPlayerX, newPlayerY))
	{
		config->player.x = newPlayerX;
		config->player.y = newPlayerY;
	}
}
