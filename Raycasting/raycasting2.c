/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:51:09 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/27 11:43:37 by sacharai         ###   ########.fr       */
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

float step(uint32_t texture_height, double wallstripheight)
{
	return (texture_height / wallstripheight);
}

int offsetx(t_ray ray, mlx_texture_t *texture)
{
	if (ray.wasvertical)
		return (((int)ray.wallhity % TILE_SIZE) * texture->width) / TILE_SIZE;
	else
		return (((int)ray.wallhitx % TILE_SIZE) * texture->width) / TILE_SIZE;
}

void	draw_up(t_config *config, double wallstripheight, int j, t_ray ray)
{
	mlx_texture_t	*texture;
	uint32_t		color;
	int				i;
	float			next_px;
	uint32_t		*pixels_tmp;

	texture = set_texture(ray, config);
	pixels_tmp = (uint32_t *)texture->pixels;
	i = 0;
	next_px = 0;
	while (i < wallstripheight / 2)
	{
		color = shift_color(pixels_tmp[texture->width * (texture->height / 2)
				+ offsetx(ray, texture) - (texture->width * (int)next_px)]);
		mlx_put_pixel(config->img, j, (HEIGHT / 2) - i, color);
		next_px += step(texture->height, wallstripheight);
		i++;
	}
}

void	draw_down(t_config *config, double wallstripheight, int j, t_ray ray)
{
	mlx_texture_t	*texture;
	uint32_t		color;
	int				i;
	float			next_px;
	uint32_t		*pixels_tmp;

	texture = set_texture(ray, config);
	pixels_tmp = (uint32_t *)texture->pixels;
	i = 0;
	next_px = 0;
	while (i < wallstripheight / 2)
	{
		color = shift_color(pixels_tmp[texture->width *(texture->height / 2)
				+ offsetx(ray, texture) + (texture->width * (int)next_px)]);
		mlx_put_pixel(config->img, j, (HEIGHT / 2) + i, color);
		next_px += step(texture->height, wallstripheight);
		i++;
	}
}

void	wall3d(t_config *config, double wallstripheight, int j, t_ray ray)
{
	draw_up(config, wallstripheight, j, ray);
	draw_down(config, wallstripheight, j, ray);
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
