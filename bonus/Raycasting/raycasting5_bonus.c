/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting5_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:58:59 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/26 23:09:55 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d_bonus.h"

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

int	is_wall(t_config *config, double x, double y)
{
	int	mx;
	int	my;

	if (x <= 0 || x >= WIDTH || y <= 0 || y >= HEIGHT)
		return (1);
	mx = floor(x / (config->map->ratiox));
	my = floor(y / (config->map->ratioy));
	if (mx < 0 || mx >= config->map->num_cols || my < 0 || \
	my >= config->map->num_rows)
		return (1);
	if (config->map->grid[my][mx] == '1')
		return (1);
	return (0);
}

void	update_player_pos(t_config *config)
{
	double	move_step;
	double	newplayer_x;
	double	newplayer_y;
	double	strafestep;

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
