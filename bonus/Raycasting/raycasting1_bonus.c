/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 00:35:41 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/27 03:13:52 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d_bonus.h"

void	initialize(t_config *config, t_map **map, mlx_t *mlx, mlx_image_t *img)
{
	config->map = *map;
	config->mlx = mlx;
	config->img = img;
	config->map->ratiox = TILE_SIZE;
	config->map->ratioy = TILE_SIZE;
	config->player.x = (*map)->player_x * (config->map->ratiox) + \
		(config->map->ratiox / 2);
	config->player.y = (*map)->player_y * (config->map->ratioy) + \
		(config->map->ratioy / 2);
	config->player.turn_direction = 0;
	config->player.walk_direction = 0;
	config->player.rotation_angle = 0;
	if (config->map->player_rotation_start == 'N')
		config->player.rotation_angle = 1.5 * M_PI;
	else if (config->map->player_rotation_start == 'S')
		config->player.rotation_angle = 0.5 * M_PI;
	else if (config->map->player_rotation_start == 'W')
		config->player.rotation_angle = M_PI;
	config->player.strafe_direction = 0;
	config->player.movement_speed = 1;
	config->player.rotation_speed = 1 * (M_PI / 180);
	config->player.fov_angle = 60 * (M_PI / 180);
	config->player.dpp = (WIDTH / 2) / tan(config->player.fov_angle / 2);
	config->map->c = 0xFFFFFFFF;
	config->map->f = 0x000000FF;
}

void	update(t_config *config)
{
	ceil2dfloor1d(config);
	update_player_pos(config);
	setup_wall(config);
	setup_map(config);
	setup_player(config);
	setup_fov(config);
	mlx_image_to_window(config->mlx, config->img, 0, 0);
}

void	hook(void *param)
{
	t_config	*config;

	config = (struct s_config *)param;
	if (key_pressed(config))
	{
		mlx_delete_image(config->mlx, config->img);
		config->img = mlx_new_image(config->mlx, WIDTH, HEIGHT);
		update(config);
		config->player.turn_direction = 0;
		config->player.walk_direction = 0;
		config->player.strafe_direction = 0;
	}
}

void	raycasting(t_map *map, mlx_t *mlx, mlx_image_t *img)
{
	t_config	*config;

	config = ft_malloc(sizeof (t_config));
	initialize(config, &map, mlx, img);
	ceil2dfloor1d(config);
	setup_map(config);
	setup_player(config);
	setup_fov(config);
	setup_wall(config);
	mlx_loop_hook(config->mlx, &hook, config);
	mlx_loop(mlx);
}
