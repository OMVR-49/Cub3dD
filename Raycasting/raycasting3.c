/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:55:52 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/26 11:38:50 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	cast_ray(t_config *config, int stripId, double rayangle)
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

void	cast_all_rays(t_config *config)
{
	double	rayangle;
	int		stripid;

	stripid = 0;
	rayangle = config->player.rotation_angle - (config->player.fov_angle / 2);
	while (stripid < NUM_RAYS)
	{
		cast_ray(config, stripid, rayangle);
		draw_line(config, config->rays[stripid].wallhitx, \
				config->rays[stripid].wallhity, 0xFF0000FF);
		rayangle += config->player.fov_angle / NUM_RAYS;
		stripid++;
	}
	mlx_image_to_window(config->mlx, config->img, 0, 0);
}

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
