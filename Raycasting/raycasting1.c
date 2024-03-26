/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 00:35:41 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/26 10:01:20 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void initialize(t_config *config, t_map **map, mlx_t *mlx, mlx_image_t *img)
{
	config->map = *map;
	config->mlx = mlx;
	config->img = img;
	config->map->ratioX = WIDTH / config->map->num_cols;
	config->map->ratioY = HEIGHT / config->map->num_rows;
	config->player.x = (*map)->playerX * (config->map->ratioX) + 
						(config->map->ratioX / 2);
	config->player.y = (*map)->playerY * (config->map->ratioY) + 
						(config->map->ratioY / 2);
	config->player.TurnDirection = 0;
	config->player.WalkDirection = 0;
	config->player.RotationAngle = 0;
	if (config->map->PlayerRotationStart == 'N')
		config->player.RotationAngle = 1.5 * M_PI;
	else if (config->map->PlayerRotationStart == 'S')
		config->player.RotationAngle = 0.5 * M_PI;
	else if (config->map->PlayerRotationStart == 'W')
		config->player.RotationAngle = M_PI;
	config->player.StrafeDirection = 0;
	config->player.MovementSpeed = 2;
	config->player.RotationSpeed = 1 * (M_PI / 180);
}

void Update(t_config *config)
{
	config->img = mlx_new_image(config->mlx, WIDTH, HEIGHT);
	UpdatePlayerPos(config);
	setup_wall(config);
	setup_map(config);
	setup_player(config);
	setup_fov(config);
	mlx_image_to_window(config->mlx, config->img, 0, 0);
}

void	Hook(void *param)
{
	t_config *config;

	config = (struct s_config *)param;
	if (KeyPressed(config))
	{
		mlx_delete_image(config->mlx, config->img);
		Update(config);
		config->player.TurnDirection = 0;
		config->player.WalkDirection = 0;
		config->player.StrafeDirection = 0;
	}
}

void raycasting(t_map *map, mlx_t *mlx, mlx_image_t *img)
{
	t_config *config;

	config = ft_malloc(sizeof (t_config));
	initialize(config, &map , mlx, img);
	setup_map(config);
	setup_player(config);
	setup_fov(config);
	setup_wall(config);
	// lkhedma kamla hna t genera l merra llwla mn be3d teb9a 3ndk function we7da li 
	// hia Update teb9a t3awd t genere based on l keys wl values li ghadi ytbedlo
	mlx_loop_hook(config->mlx, &Hook, config);
	mlx_loop(mlx);
}
