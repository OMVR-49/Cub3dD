/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:51:09 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/26 21:13:27 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

uint32_t	set_color(t_ray ray)
{
	if (ray.wasvertical && ray.israyfdown)
		return (0x00FF00FF);
	else if (ray.wasvertical && ray.israyfup)
		return (0xFDEE00FF);
	else if (!ray.wasvertical && ray.israyfright)
		return (0x0048BAFF);
	else if (!ray.wasvertical && ray.israyfleft)
		return (0xC1CDCDFF);
	return (0);
}

void	wall3d(t_config *config, double wallstripheight, int j, t_ray ray)
{
	uint32_t	color;
	int			i;

	i = 0;
	color = set_color(ray);
	while (i < wallstripheight / 2)
	{
		mlx_put_pixel(config->img, j, (HEIGHT / 2) - i, color);
		i++;
	}
	i = 0;
	while (i < wallstripheight / 2)
	{
		mlx_put_pixel(config->img, j, (HEIGHT / 2) + i, color);
		i++;
	}
}

void	ceil2dfloor1d(t_config *config, int i)
{
	int	j;

	j = 0;
	while (j < HEIGHT)
	{
		if (j < HEIGHT / 2)
			mlx_put_pixel(config->img, i, j, config->map->c);
		if (j > HEIGHT / 2)
			mlx_put_pixel(config->img, i, j, config->map->f);
		j++;
	}
}

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
		ceil2dfloor1d(config, i);
		wall3d(config, config->rays[i].wallstripheight, i, config->rays[i]);
		i++;
	}
	mlx_image_to_window(config->mlx, config->img, 0, 0);
}

void	cast_all_rays(t_config *config)
{
	double	rayangle;
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
