/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:57:48 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/27 05:30:17 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	whileforvert(t_config *config, t_ray *ray, double nvtx, double nvty)
{
	double	xtocheck;
	double	ytocheck;

	ray->wallhitxv = nvtx;
	ray->wallhityv = nvty;
	while (nvtx >= 0 && nvtx < config->map->map_width && nvty >= 0 && nvty < config->map->map_height)
	{
		if (ray->israyfleft)
			xtocheck = nvtx - 1;
		else
			xtocheck = nvtx;
		ytocheck = nvty;
		if (ray->israyfleft)
			xtocheck--;
		if (is_wall(config, xtocheck, ytocheck))
		{
			ray->foundhitvertical = true;
			ray->wallhitxv = nvtx;
			ray->wallhityv = nvty;
			break ;
		}
		else
		{
			nvtx += ray->xincv;
			nvty += ray->yincv;
		}
	}
}

void	cast_vertical_ray(t_config *config, t_ray *ray)
{
	double	nextverttouchx;
	double	nextverttouchy;
	double	yintercept;
	double	xintercept;

	xintercept = floor(config->player.x / (config->map->ratiox)) * \
	(config->map->ratiox);
	if (ray->israyfright)
		xintercept += (config->map->ratiox);
	yintercept = config->player.y + (xintercept - config->player.x) * \
	tan(ray->rayangle);
	ray->xincv = config->map->ratiox;
	ray->yincv = ray->xincv * tan(ray->rayangle);
	if (ray->israyfleft)
		ray->xincv *= -1;
	if (ray->israyfup && ray->yincv > 0)
		ray->yincv *= -1;
	if (ray->israyfdown && ray->yincv < 0)
		ray->yincv *= -1;
	nextverttouchx = xintercept;
	nextverttouchy = yintercept;
	whileforvert(config, ray, nextverttouchx, nextverttouchy);
}

void	whileforhorz(t_config *config, t_ray *ray, double nhtx, double nhty)
{
	double	xtocheck;
	double	ytocheck;

	ray->wallhitxh = nhtx;
	ray->wallhityh = nhty;
	while (nhtx >= 0 && nhtx < config->map->map_width && nhty >= 0 && nhty < config->map->map_height)
	{
		xtocheck = nhtx;
		if (ray->israyfup)
			ytocheck = nhty - 1;
		else
			ytocheck = nhty;
		if (is_wall(config, xtocheck, ytocheck))
		{
			ray->foundhithorizontal = true;
			ray->wallhitxh = nhtx;
			ray->wallhityh = nhty;
			break ;
		}
		else
		{
			nhtx += ray->xinch;
			nhty += ray->yinch;
		}
	}
}

void	cast_horizontal_ray(t_config *config, t_ray *ray)
{
	double	nexthorztouchx;
	double	nexthorztouchy;
	double	yintercept;
	double	xintercept;

	yintercept = floor(config->player.y / (config->map->ratioy)) * \
	(config->map->ratioy);
	if (ray->israyfdown)
		yintercept += config->map->ratioy;
	xintercept = config->player.x + (yintercept - config->player.y) / \
	tan(ray->rayangle);
	ray->yinch = config->map->ratioy;
	ray->xinch = ray->yinch / tan(ray->rayangle);
	if (ray->israyfup)
		ray->yinch *= -1;
	if (ray->israyfleft && ray->xinch > 0)
		ray->xinch *= -1;
	if (ray->israyfright && ray->xinch < 0)
		ray->xinch *= -1;
	nexthorztouchx = xintercept;
	nexthorztouchy = yintercept;
	whileforhorz(config, ray, nexthorztouchx, nexthorztouchy);
}

void	find_closest_wall_hit(t_config *config, t_ray *ray)
{
	if (ray->foundhithorizontal)
		ray->h_distance = distance_between_points(config->player.x, \
		config->player.y, ray->wallhitxh, ray->wallhityh);
	else
		ray->h_distance = INT_MAX;
	if (ray->foundhitvertical)
		ray->v_distance = distance_between_points(config->player.x, \
		config->player.y, ray->wallhitxv, ray->wallhityv);
	else
		ray->v_distance = INT_MAX;
	if (ray->v_distance < ray->h_distance)
	{
		ray->wallhitx = ray->wallhitxv;
		ray->wallhity = ray->wallhityv;
		ray->distance = ray->v_distance;
	}
	else
	{
		ray->wallhitx = ray->wallhitxh;
		ray->wallhity = ray->wallhityh;
		ray->distance = ray->h_distance;
		ray->wasvertical = true;
	}
}
