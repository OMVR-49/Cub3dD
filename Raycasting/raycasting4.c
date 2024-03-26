/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:57:48 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/26 09:58:41 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"


void	whileForVert(t_config *config, t_ray *ray, double nextVertTouchX, double nextVertTouchY)
{
	double xToCheck;
	double yToCheck;

	while(nextVertTouchX >= 0 && nextVertTouchX <= WIDTH && nextVertTouchY >= 0 && nextVertTouchY <= HEIGHT)
	{
		if(ray->isRayFacingLeft)
			xToCheck = nextVertTouchX - 1;
		else
			xToCheck = nextVertTouchX;
		yToCheck = nextVertTouchY;
		if (ray->isRayFacingLeft)
			xToCheck--;
		if(isWall(config, xToCheck, yToCheck))
		{
			ray->foundHitVertical = true;
			ray->wallHitXV = nextVertTouchX;
			ray->wallHitYV = nextVertTouchY;
			break;
		}
		else
		{
			nextVertTouchX += ray->XincV;
			nextVertTouchY += ray->YincV;
		}
	}
}

void	castVerticalRay(t_config *config, t_ray *ray)
{
	double yintercept;
	double xintercept;
	double nextVertTouchX;
	double nextVertTouchY;

	xintercept = floor(config->player.x / (config->map->ratioX)) * ( config->map->ratioX);
	if (ray->isRayFacingRight)
		xintercept += (config->map->ratioX);
	yintercept = config->player.y + (xintercept - config->player.x) * tan(ray->rayAngle);
	ray->XincV = config->map->ratioX;
	if (ray->isRayFacingLeft)
		ray->XincV *= -1;
	ray->YincV = ray->XincV * tan(ray->rayAngle);
	if(ray->isRayFacingUp && ray->YincV > 0)
		ray->YincV *= -1;
	if(ray->isRayFacingDown && ray->YincV < 0)
		ray->YincV *= -1;
	nextVertTouchX = xintercept;
	nextVertTouchY = yintercept;
	whileForVert(config, ray, nextVertTouchX, nextVertTouchY);
}


void	whileForHorz(t_config *config, t_ray *ray, double nextHorzTouchX, double nextHorzTouchY)
{
	double xToCheck;
	double yToCheck;

	while(nextHorzTouchX >= 0 && nextHorzTouchX <= WIDTH && nextHorzTouchY >= 0 && nextHorzTouchY <= HEIGHT)
	{
		xToCheck = nextHorzTouchX;
		if(ray->isRayFacingUp)
			yToCheck = nextHorzTouchY - 1;
		else
			yToCheck = nextHorzTouchY;
		if (isWall(config, xToCheck, yToCheck))
		{
			ray->foundHitHorizontal = true;
			ray->wallHitXH = nextHorzTouchX;
			ray->wallHitYH = nextHorzTouchY;
			break;
		}
		else
		{
			nextHorzTouchX += ray->XincH;
			nextHorzTouchY += ray->YincH;
		}
	}
}


void	castHorizontalRay(t_config *config, t_ray *ray)
{
	double yintercept;
	double xintercept;
	double nextHorzTouchX;
	double nextHorzTouchY;

	yintercept = floor(config->player.y / (config->map->ratioY)) * (config->map->ratioY);
	if (ray->isRayFacingDown)
		yintercept += config->map->ratioY;
	xintercept = config->player.x + (yintercept - config->player.y) / tan(ray->rayAngle);
	ray->YincH = config->map->ratioY;
	if (ray->isRayFacingUp)
		ray->YincH *= -1;
	ray->XincH = ray->YincH / tan(ray->rayAngle);
	if(ray->isRayFacingLeft && ray->XincH > 0)
		ray->XincH *= -1;
	if(ray->isRayFacingRight && ray->XincH < 0)
		ray->XincH *= -1;
	nextHorzTouchX = xintercept;
	nextHorzTouchY = yintercept;
	whileForHorz(config, ray, nextHorzTouchX, nextHorzTouchY);
}



void	findClosestWallHit(t_config *config, t_ray *ray)
{
	double hDistance;
	double vDistance;

	if (ray->foundHitHorizontal)
		hDistance = distanceBetweenPoints(config->player.x, config->player.y, ray->wallHitXH, ray->wallHitYH);
	else
		hDistance = INT_MAX;
	if (ray->foundHitVertical)
		vDistance = distanceBetweenPoints(config->player.x, config->player.y, ray->wallHitXV, ray->wallHitYV);
	else
		vDistance = INT_MAX;
	if (vDistance < hDistance)
	{
		ray->wallHitX = ray->wallHitXV;
		ray->wallHitY = ray->wallHitYV;
		ray->distance = vDistance;
	}
	else
	{
		ray->wallHitX = ray->wallHitXH;
		ray->wallHitY = ray->wallHitYH;
		ray->distance = hDistance;
		ray->wasvertical = true;
	}
}