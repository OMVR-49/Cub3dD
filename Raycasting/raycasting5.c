/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:41:05 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/28 02:36:31 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	draw_up(t_config *config, float wallstripheight, int j, t_ray ray)
{
	mlx_texture_t	*texture;
	uint32_t		color;
	int				i;
	float			next_px;
	uint32_t		*pixels_tmp;

	texture = set_texture(ray, config);
	pixels_tmp = (uint32_t *)texture->pixels;
	ray.step = step(texture->height, wallstripheight);
	if (wallstripheight > HEIGHT)
		wallstripheight = HEIGHT;
	i = HEIGHT / 2;
	next_px = 0;
	while (i > (HEIGHT / 2) - (wallstripheight / 2))
	{
		color = shift_color(pixels_tmp[texture->width * (texture->height / 2)
				+ offsetx(ray, texture) - (texture->width * (int)next_px)]);
		mlx_put_pixel(config->img, j, i, color);
		next_px += ray.step;
		i--;
	}
}

void	draw_down(t_config *config, float wallstripheight, int j, t_ray ray)
{
	mlx_texture_t	*texture;
	uint32_t		color;
	int				i;
	float			next_px;
	uint32_t		*pixels_tmp;

	texture = set_texture(ray, config);
	pixels_tmp = (uint32_t *)texture->pixels;
	ray.step = step(texture->height, wallstripheight);
	if (wallstripheight > HEIGHT)
		wallstripheight = HEIGHT;
	i = HEIGHT / 2;
	next_px = 0;
	while (i < (HEIGHT / 2) + (wallstripheight / 2))
	{
		if (texture->width * texture->height < texture->width
			* (texture->height / 2)
			+ offsetx(ray, texture) + (texture->width * (int)next_px))
			return (mlx_put_pixel(config->img, j, i, 0x7FFFFFFF));
		color = shift_color(pixels_tmp[texture->width *(texture->height / 2)
				+ offsetx(ray, texture) + (texture->width * (int)next_px)]);
		mlx_put_pixel(config->img, j, i, color);
		next_px += ray.step;
		i++;
	}
}

void	wall3d(t_config *config, float wallstripheight, int j, t_ray ray)
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
	float	ray_distance;
	int		i;

	i = 0;
	while (i < NUM_RAYS)
	{
		ray_distance = config->rays[i].distance * \
			cos(config->rays[i].rayangle - config->player.rotation_angle);
		config->rays[i].wallstripheight = \
			(TILE_SIZE / ray_distance) * config->player.dpp;
		ceil2dfloor1d(config, i);
		wall3d(config, config->rays[i].wallstripheight, i, config->rays[i]);
		i++;
	}
	mlx_image_to_window(config->mlx, config->img, 0, 0);
}
