/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:55:52 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/26 09:57:29 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void castRay(t_config *config, int stripId, double rayAngle)
{
	t_ray *ray;

	ray = &config->rays[stripId];
	ray->rayAngle = normalizeAngle(rayAngle);
	ray->isRayFacingDown = (ray->rayAngle > 0 && ray->rayAngle < M_PI);
	ray->isRayFacingUp = !ray->isRayFacingDown;
	ray->isRayFacingLeft = (ray->rayAngle >  M_PI_2 && ray->rayAngle < 3 * M_PI_2); 
	ray->isRayFacingRight = !ray->isRayFacingLeft;
	ray->foundHitHorizontal = false;
	ray->foundHitVertical = false;
	ray->wallHitXH = 0;
	ray->wallHitYH = 0;
	ray->wallHitXV = 0;
	ray->wallHitYV = 0;
	ray->wallHitX = 0;
	ray->wallHitY = 0;
	ray->distance = 0;
	ray->wasvertical = false;
	castHorizontalRay(config, ray);
	castVerticalRay(config, ray);
	findClosestWallHit(config, ray);
}

void	castAllRays(t_config *config)
{
	int stripId;
	double rayAngle;

	stripId = 0;
	rayAngle = config->player.RotationAngle - (FOV_ANGLE / 2);
	while(stripId < NUM_RAYS) 
	{
		castRay(config, stripId, rayAngle);
		draw_line(config,config->rays[stripId].wallHitX , config->rays[stripId].wallHitY, 0xFF0000FF); // check
		rayAngle += FOV_ANGLE / NUM_RAYS;
		stripId++;
	}
	mlx_image_to_window(config->mlx, config->img, 0, 0);
}

uint32_t	set_color(t_ray ray)
{
	if (ray.wasvertical &&  ray.isRayFacingDown )
		return (0x00FF00FF);
	else if (ray.wasvertical &&  ray.isRayFacingUp )
		return (0xFDEE00FF);
	else if (!ray.wasvertical && ray.isRayFacingRight)
		return (0x0048BAFF);
	else if (!ray.wasvertical && ray.isRayFacingLeft)
		return (0xC1CDCDFF);
	return 0;
}

void 	wall3D(t_config *config, double wallStripHeight, int j, t_ray ray)
{
	int i;
	uint32_t color;

	i = 0;
	color = set_color(ray);
	while (i < wallStripHeight/2)
	{
		mlx_put_pixel(config->img, j, (HEIGHT / 2) - i, color);
		i++;
	}
	i = 0;
	while (i < wallStripHeight / 2)
	{
		mlx_put_pixel(config->img, j, (HEIGHT / 2) + i, color);
		i++;
	}
}

void	ceil2DFloor1D(t_config *config, int i)
{
	int j;

	j = 0;	
	while(j < HEIGHT)
	{
		if (j < HEIGHT / 2)
			mlx_put_pixel(config->img, i, j, config->map->c);
		if (j > HEIGHT / 2)
			mlx_put_pixel(config->img, i, j, config->map->f);
		j++;
	}
	
}
