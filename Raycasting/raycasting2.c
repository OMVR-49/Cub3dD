/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:51:09 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/26 10:03:36 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	setup_wall(t_config *config)
{
	int i;
	double rayDistance;

	i = 0;
	while (i < NUM_RAYS)
	{
		rayDistance = config->rays[i].distance * cos(config->rays[i].rayAngle - config->player.RotationAngle);
		config->rays[i].wallStripHeight = (config->map->ratioY / rayDistance) * dPP; // maybe replace width by numcos
		if (config->rays[i].wallStripHeight > HEIGHT)
			config->rays[i].wallStripHeight = HEIGHT;
		ceil2DFloor1D(config, i);
		wall3D(config, config->rays[i].wallStripHeight, i, config->rays[i]);
		i++;
	}
}

void	setup_fov(t_config *config)
{
	castAllRays(config);
}

void	setup_player(t_config *config)
{
	mlx_put_pixel(config->img, config->player.x * MAP_Scale, config->player.y * MAP_Scale ,0xFF2E2EFF);
}


void grid(t_config *config, int tileX , int tileY, uint32_t tileColor)
{
	int x;
	int y;
	double pixelX;
	double pixelY;
	
	y = 0;
	while(y <= config->map->ratioY)
	{
		x = 0;
		while(x <= config->map->ratioX)
		{
			pixelX = tileX + x;
			pixelY = tileY + y;
			if (pixelX < WIDTH && pixelY < HEIGHT)
				mlx_put_pixel(config->img, pixelX * MAP_Scale, pixelY * MAP_Scale, tileColor);
			x++;
		}
		y++;
	}
}

void setup_map(t_config *config)
{
	uint32_t tileColor;
	int tileY;
	int tileX;
	int x;
	int y;

	tileY = 0;
	y = 0;
	while (y < config->map->num_rows)
	{
		tileX = 0;
		x = 0;
		while (x < config->map->num_cols)
		{
			if(config->map->grid[y][x] == '1')
				tileColor = 0x2E2EFFFF;
			else if (config->map->grid[y][x] == '0')
				tileColor = 0xFFFFFFFF;
			else if(config->map->grid[y][x] == ' ')
				tileColor = 0x000000FF;
			grid(config, tileX, tileY, tileColor);
			tileX += config->map->ratioX;
			x++;
		}
		tileY += config->map->ratioY;
		y++;
}
mlx_image_to_window(config->mlx, config->img, 0, 0);
}
