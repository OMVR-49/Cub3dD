/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:51:09 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/27 13:12:50 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

uint32_t	shift_color(uint32_t color)
{
	uint32_t	green;
	uint32_t	blue;
	uint32_t	red;
	uint32_t	a;

	blue = (color >> 8) & 0xFF00;
	red = (color << 24) & 0xFF000000;
	green = (color << 8) & 0xFF0000;
	a = (color >> 24) & 0xFF;
	return (green | red | blue | a);
}

mlx_texture_t	*set_texture(t_ray ray, t_config *config)
{
	if (ray.wasvertical && ray.israyfleft)
		return (mlx_load_png(config->map->we));
	else if (ray.wasvertical && ray.israyfright)
		return (mlx_load_png(config->map->ea));
	else if (!ray.wasvertical && ray.israyfup)
		return (mlx_load_png(config->map->no));
	else
		return (mlx_load_png(config->map->so));
}

double	step(uint32_t texture_height, double wallstripheight)
{
	return (texture_height / wallstripheight);
}

int	offsetx(t_ray ray, mlx_texture_t *texture)
{
	if (ray.wasvertical)
		return ((((int)ray.wallhity % TILE_SIZE) * texture->width) / TILE_SIZE);
	else
		return ((((int)ray.wallhitx % TILE_SIZE) * texture->width) / TILE_SIZE);
}
