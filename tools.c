/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 01:09:34 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/26 10:44:52 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	draw_line(t_config *config, double endX, double endY, uint32_t color)
{
	double	deltax;
	double	deltay;
	double	pixelx;
	double	pixely;
	double	pixels;

	deltax = endX - config->player.x;
	deltay = endY - config->player.y;
	pixels = sqrt((deltax * deltax) + (deltay * deltay));
	deltax /= pixels;
	deltay /= pixels;
	pixelx = config->player.x;
	pixely = config->player.y;
	while (pixels > 0)
	{
		mlx_put_pixel(config->img, pixelx * MAP_SCALE, pixely * MAP_SCALE,
			color);
		pixelx += deltax;
		pixely += deltay;
		--pixels;
	}
	return (1);
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

double	distance_between_points(double x, double y, double a, double b)
{
	return (sqrt((a - x) * (a - x) + (b - y) * (b - y)));
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	else if (angle > (2 * M_PI))
		angle = angle - (2 * M_PI);
	return (angle);
}
