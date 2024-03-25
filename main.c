/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:39:27 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/24 22:16:37 by ojebbari         ###   ########.fr       */
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
	(*map) = ft_malloc(sizeof(t_map));
	(*map)->grid = ft_malloc(8 * sizeof(char *));
	while (i < 8)
	{
		(*map)->grid[i] = ft_malloc(8 * sizeof(char));
		i++;
	}
	(*map)->grid[0] = "11111111";
	(*map)->grid[1] = "10000001";
	(*map)->grid[2] = "10010001";
	(*map)->grid[3] = "10000101";
	(*map)->grid[4] = "10100001";
	(*map)->grid[5] = "10000001";
	(*map)->grid[6] = "10000001";
	(*map)->grid[7] = "11111111";
	(*map)->num_cols = 8;
	(*map)->num_rows = 8;
	(*map)->playerX = 3;
	(*map)->playerY = 5;
	// (*map)->playerStart = 'N';
	// (*map)->img_Height = (*map)->num_rows * TileSize;
	// (*map)->img_Width = (*map)->num_cols * TileSize;;
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
			if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
				exit(EXIT_FAILURE);
			img = mlx_new_image(mlx, WIDTH, HEIGHT);
			raycasting(map, mlx, img);
		}
	}
	else
		ft_error(1);
	mlx_terminate(mlx);
}
