/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 01:09:34 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/26 09:53:04 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int draw_line(t_config *config, double endX, double endY, uint32_t color)
{
	double deltaX;
	double deltaY;
	double pixelX;
	double pixelY;
	double pixels ;

	deltaX = endX - config->player.x;
	deltaY = endY - config->player.y;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels; 
	pixelX = config->player.x;
	pixelY = config->player.y;
	while (pixels > 0)
	{
		mlx_put_pixel(config->img, pixelX * MAP_Scale, pixelY * MAP_Scale,  color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
	return 1;
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("malloc fails\n");
		exit(1);
	}
	return (ptr);
}

double distanceBetweenPoints(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

double normalizeAngle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	else if (angle > (2 * M_PI))
		angle = angle - (2 * M_PI);
	return (angle);
}
