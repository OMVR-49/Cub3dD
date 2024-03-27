/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:51:09 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/27 22:24:56 by sacharai         ###   ########.fr       */
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
		return (config->texture_we);
	else if (ray.wasvertical && ray.israyfright)
		return (config->texture_ea);
	else if (!ray.wasvertical && ray.israyfup)
		return (config->texture_no);
	else
		return (config->texture_so);
}

float	step(uint32_t texture_height, float wallstripheight)
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
