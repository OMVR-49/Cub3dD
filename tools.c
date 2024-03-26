/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 01:09:34 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/26 06:05:12 by ojebbari         ###   ########.fr       */
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

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
void set_rgba(int color)
{
	
}