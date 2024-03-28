/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:55:52 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/27 15:09:34 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	cast_ray(t_config *config, int stripId, float rayangle)
{
	t_ray	*ray;

	ray = &config->rays[stripId];
	ray->rayangle = normalize_angle(rayangle);
	ray->israyfdown = (ray->rayangle > 0 && ray->rayangle < M_PI);
	ray->israyfup = !ray->israyfdown;
	ray->israyfleft = (ray->rayangle > M_PI_2 && ray->rayangle < 3 * \
			M_PI_2);
	ray->israyfright = !ray->israyfleft;
	ray->foundhithorizontal = false;
	ray->foundhitvertical = false;
	ray->wallhitxh = 0;
	ray->wallhityh = 0;
	ray->wallhitxv = 0;
	ray->wallhityv = 0;
	ray->wallhitx = 0;
	ray->wallhity = 0;
	ray->distance = 0;
	ray->wasvertical = false;
	cast_horizontal_ray(config, ray);
	cast_vertical_ray(config, ray);
	find_closest_wall_hit(config, ray);
}

void	setup_fov(t_config *config)
{
	cast_all_rays(config);
}

int	key_pressed(t_config *config)
{
	int	i;

	i = 0;
	if (mlx_is_key_down(config->mlx, MLX_KEY_S))
		config->player.walk_direction = -1 + (0 * i++);
	if (mlx_is_key_down(config->mlx, MLX_KEY_W))
		config->player.walk_direction = 1 + (0 * i++);
	if (mlx_is_key_down(config->mlx, MLX_KEY_RIGHT))
		config->player.turn_direction = 1 + (0 * i++);
	if (mlx_is_key_down(config->mlx, MLX_KEY_LEFT))
		config->player.turn_direction = -1 + (0 * i++);
	if (mlx_is_key_down(config->mlx, MLX_KEY_D))
		config->player.strafe_direction = 1 + (0 * i++);
	if (mlx_is_key_down(config->mlx, MLX_KEY_A))
		config->player.strafe_direction = -1 + (0 * i++);
	if (mlx_is_key_down(config->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(config->mlx);
	return (i);
}

int	is_wall(t_config *config, float x, float y)
{
	int	mx;
	int	my;

	if (x < 0 || x >= config->map->map_width || y < 0 || \
	y >= config->map->map_height)
		return (1);
	mx = floor(x / (TILE_SIZE));
	my = floor(y / (TILE_SIZE));
	if (mx < 0 || mx >= config->map->num_cols || my < 0 || \
	my >= config->map->num_rows)
		return (1);
	if (config->map->grid[my][mx] == '1')
		return (1);
	return (0);
}

void	update_player_pos(t_config *config)
{
	float	move_step;
	float	newplayer_x;
	float	newplayer_y;
	float	strafestep;

	config->player.rotation_angle += config->player.turn_direction * \
	config->player.rotation_speed;
	move_step = config->player.walk_direction * config->player.movement_speed;
	newplayer_x = config->player.x + cos(config->player.rotation_angle) * \
	move_step;
	newplayer_y = config->player.y + sin(config->player.rotation_angle) * \
	move_step;
	strafestep = config->player.strafe_direction * \
	config->player.movement_speed;
	newplayer_x += cos(config->player.rotation_angle + M_PI_2) * strafestep;
	newplayer_y += sin(config->player.rotation_angle + M_PI_2) * strafestep;
	if (!is_wall(config, newplayer_x, newplayer_y))
	{
		config->player.x = newplayer_x;
		config->player.y = newplayer_y;
	}
}
