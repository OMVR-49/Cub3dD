/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 00:35:41 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/13 06:48:11 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void initialize(t_config *config)
{
	config->player.x = 0; //ps: search for x placement of the config in the array
	config->player.y = 0; //ps: search for y placement of the config in the array
	config->player.Raduis = 3;
	config->player.RotationSpeed = floor((double)(3 * (M_PI / 180)));
	config->player.TurnDirection = 0;
	config->player.WalkDirection = 0;
	config->player.RotationAngle = 0;
	config->player.MovementSpeed = 3;
	
}

void setup_mlx(t_config *config)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
	config->mlx = mlx_init(256, 256, "Cub3d", true);
	if (!config->mlx)
		exit(EXIT_FAILURE);
	(config->img) = mlx_new_image(config->mlx, 256, 256);
	if (!config->img || (mlx_image_to_window(config->mlx, config->img, 0, 0) < 0))
		exit(EXIT_FAILURE);
}

void setup_map(t_config *map)
{

}

void raycasting(char **m)
{
	t_config *config;

	config = ft_malloc(sizeof (t_config));
	initialize(config);
	setup_mlx(config);
	setup_map(config);
	
	return (EXIT_SUCCESS);
}