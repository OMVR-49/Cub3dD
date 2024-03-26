/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:51:09 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/26 22:17:06 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d_bonus.h"

void	setup_wall(t_config *config)
{
	double	ray_distance;
	int		i;

	i = 0;
	while (i < NUM_RAYS)
	{
		ray_distance = config->rays[i].distance * \
			cos(config->rays[i].rayangle - config->player.rotation_angle);
		config->rays[i].wallstripheight = \
			(config->map->ratioy / ray_distance) * config->player.dpp;
		if (config->rays[i].wallstripheight > HEIGHT)
			config->rays[i].wallstripheight = HEIGHT;
		wall3d(config, config->rays[i].wallstripheight, i, config->rays[i]);
		i++;
	}
	mlx_image_to_window(config->mlx, config->img, 0, 0);
}

void	setup_fov(t_config *config)
{
	cast_all_rays(config);
}

void	setup_player(t_config *config)
{
	mlx_put_pixel(config->img, config->player.x * MAP_SCALE,
		config->player.y * MAP_SCALE, 0xFF2E2EFF);
	mlx_image_to_window(config->mlx, config->img, 0, 0);
}

void	grid(t_config *config, int tileX, int tileY, uint32_t tileColor)
{
	double	pixelx;
	double	pixely;
	int		x;
	int		y;

	y = 0;
	while (y <= config->map->ratioy)
	{
		x = 0;
		while (x <= config->map->ratiox)
		{
			pixelx = tileX + x;
			pixely = tileY + y;
			if (pixelx < WIDTH && pixely < HEIGHT)
				mlx_put_pixel(config->img, pixelx * MAP_SCALE, pixely * \
					MAP_SCALE, tileColor);
			x++;
		}
		y++;
	}
}

void	setup_map(t_config *config)
{
	uint32_t	tile_color;
	int			tilex;
	int			tiley;
	int			x;
	int			y;

	tiley = 0;
	y = 0;
	while (y < config->map->num_rows)
	{
		tilex = 0;
		x = 0;
		while (x < config->map->num_cols)
		{
			if (config->map->grid[y][x] == '1')
				tile_color = 0x2E2EFFFF;
			else if (config->map->grid[y][x] == '0')
				tile_color = 0xFFFFFFFF;
			grid(config, tilex, tiley, tile_color);
			tilex += config->map->ratiox + (0 * x++);
		}
		tiley += config->map->ratioy;
		y++;
	}
	mlx_image_to_window(config->mlx, config->img, 0, 0);
}
