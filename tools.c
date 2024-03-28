/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 01:09:34 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/27 20:15:41 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	draw_line(t_config *config, float endX, float endY, uint32_t color)
{
	float	deltax;
	float	deltay;
	float	pixelx;
	float	pixely;
	float	pixels;

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
	ft_lstadd_back_clctr(ft_collector(), ft_lstnew_clctr(ptr));
	return (ptr);
}

float	distance_between_points(float x, float y, float a, float b)
{
	return (sqrt((a - x) * (a - x) + (b - y) * (b - y)));
}

float	normalize_angle(float angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	else if (angle > (2 * M_PI))
		angle = angle - (2 * M_PI);
	return (angle);
}
