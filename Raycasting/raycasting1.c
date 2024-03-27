/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 00:35:41 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/27 22:24:39 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	initialize(t_config *config, t_map **map, mlx_t *mlx, mlx_image_t *img)
{
	config->map = *map;
	config->map->map_width = TILE_SIZE * config->map->num_cols;
	config->map->map_height = TILE_SIZE * config->map->num_rows;
	config->mlx = mlx;
	config->img = img;
	config->player.x = (*map)->player_x * (TILE_SIZE) + (TILE_SIZE / 2);
	config->player.y = (*map)->player_y * (TILE_SIZE) + (TILE_SIZE / 2);
	config->player.turn_direction = 0;
	config->player.walk_direction = 0;
	config->player.strafe_direction = 0;
	config->player.rotation_angle = 0;
	if (config->map->player_rotation_start == 'N')
		config->player.rotation_angle = 1.5 * M_PI;
	else if (config->map->player_rotation_start == 'S')
		config->player.rotation_angle = 0.5 * M_PI;
	else if (config->map->player_rotation_start == 'W')
		config->player.rotation_angle = M_PI;
	config->player.movement_speed = 2;
	config->player.rotation_speed = 2 * (M_PI / 180);
	config->player.fov_angle = 60 * (M_PI / 180);
	config->player.dpp = (WIDTH / 2) / tan(config->player.fov_angle / 2);
	config->texture_no = mlx_load_png(config->map->no);
	config->texture_so = mlx_load_png(config->map->so);
	config->texture_we = mlx_load_png(config->map->we);
	config->texture_ea = mlx_load_png(config->map->ea);
}

void	update(t_config *config)
{
	update_player_pos(config);
	setup_wall(config);
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

void	cast_all_rays(t_config *config)
{
	float	rayangle;
	int		stripid;

	stripid = 0;
	rayangle = config->player.rotation_angle - (config->player.fov_angle / 2);
	while (stripid < NUM_RAYS)
	{
		cast_ray(config, stripid, rayangle);
		rayangle += config->player.fov_angle / NUM_RAYS;
		stripid++;
	}
}

t_config	raycasting(t_map *map, mlx_t *mlx, mlx_image_t *img)
{
	t_config	config;

	initialize(&config, &map, mlx, img);
	setup_fov(&config);
	setup_wall(&config);
	mlx_loop_hook(config.mlx, &hook, &config);
	mlx_loop(mlx);
	return (config);
}
