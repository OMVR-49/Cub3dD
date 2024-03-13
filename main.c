/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:39:27 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/09 20:17:01 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int ft_error(int x)
{
	if (x == 1)
		perror("Invalid Arguments");
	else if (x = 2)
		perror("");
	else if (x = 3)
		perror("");
	exit(x);
}

int main(int ac, char **av)
{
	char **m;

	if (ac == 2)
	{
		m = parsing(ac, av);
		if (m)
			raycasting(m);
	}
	else
		ft_error(1);
}