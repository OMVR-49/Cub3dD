/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:41:05 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/27 13:58:56 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	draw_up(t_config *config, double wallstripheight, int j, t_ray ray)
{
	mlx_texture_t	*texture;
	uint32_t		color;
	int				i;
	double			next_px;
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
	double			next_px;
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
			(TILE_SIZE / ray_distance) * config->player.dpp;
		if (config->rays[i].wallstripheight > HEIGHT)
			config->rays[i].wallstripheight = HEIGHT;
		ceil2dfloor1d(config, i);
		wall3d(config, config->rays[i].wallstripheight, i, config->rays[i]);
		i++;
	}
	mlx_image_to_window(config->mlx, config->img, 0, 0);
}
