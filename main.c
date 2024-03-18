/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:39:27 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/18 03:19:52 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int ft_error(int x)
{
	if (x == 1)
		perror("Invalid Argumentss");
	else if (x == 2)
		perror("");
	else if (x == 3)
		perror("");
	exit(x);
}

void	test(t_map **map)
{
	int i = 0;
	int j = 0;

	(*map) = ft_malloc(sizeof(t_map));
	(*map)->grid = ft_malloc(4 * sizeof(char *));
	(*map)->grid[0] = ft_malloc(4);
	(*map)->grid[1] = ft_malloc(4);
	(*map)->grid[2] = ft_malloc(4);
	(*map)->grid[3] = ft_malloc(4);
	(*map)->grid[0][0] = 1;
	(*map)->grid[0][1] = 1;
	(*map)->grid[0][2] = 1;
	(*map)->grid[0][3] = 1;
	(*map)->grid[1][0] = 1;
	(*map)->grid[1][1] = 0;
	(*map)->grid[1][2] = 0;
	(*map)->grid[1][3] = 1;
	(*map)->grid[2][0] = 1;
	(*map)->grid[2][1] = 0;
	(*map)->grid[2][2] = 0;
	(*map)->grid[2][3] = 1;
	(*map)->grid[3][0] = 1;
	(*map)->grid[3][1] = 1;
	(*map)->grid[3][2] = 1;
	(*map)->grid[3][3] = 1;
	(*map)->Height = 4;
	(*map)->Width = 4;
}
int main(int ac, char **av)
{
	t_map *map;
	mlx_t *mlx;
	mlx_image_t *img;

	test(&map);
	if (ac == 1) // 1 bach ntester bla parsing
	{
		// map = parsing(ac, av);
		if (map)
		{
			mlx_set_setting(0, true);
			if (!(mlx = mlx_init(800, 800, "MLX42", true)))
				exit(EXIT_FAILURE);
			img = mlx_new_image(mlx, WIDTH, HEIGHT);
			if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
				exit(EXIT_FAILURE);
			if (raycasting(map, mlx, img))
				return(EXIT_SUCCESS);
		}
	}
	else
		ft_error(1);
}
