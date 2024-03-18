/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 01:09:34 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/18 03:21:39 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

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