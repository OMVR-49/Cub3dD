/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:39:27 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/26 03:11:25 by ojebbari         ###   ########.fr       */
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
	(*map)->grid = ft_malloc(27 * sizeof(char *));
	while (i < 27)
	{
		(*map)->grid[i] = ft_malloc(29 * sizeof(char));
		i++;
	}
	(*map)->grid[0] = "11111111111111111111111111111";
	(*map)->grid[1] = "10000000000000000000000000001";
	(*map)->grid[2] = "10000000000000000000000000001";
	(*map)->grid[3] = "10000000000000000000000000001";
	(*map)->grid[4] = "10000000000000000000000000001";
	(*map)->grid[5] = "10000000000000000000000000001";
	(*map)->grid[6] = "10000000000000000000000000001";
	(*map)->grid[7] = "10000000000000000000000000001";
	(*map)->grid[8] = "10000000000000000000000000001";
	(*map)->grid[9] = "10000000000000010000000000001";
	(*map)->grid[10] = "10000000000000000000000000001";
	(*map)->grid[11] = "10000000000000000000000000001";
	(*map)->grid[12] = "10000000000000000000000000001";
	(*map)->grid[13] = "10000000000000000000000000001";
	(*map)->grid[14] = "10000000000000000000000000001";
	(*map)->grid[15] = "10000000000010000000000000001";
	(*map)->grid[16] = "10000000000000000000000000001";
	(*map)->grid[17] = "10000000000000000000000000001";
	(*map)->grid[18] = "10000000000000000000000000001";
	(*map)->grid[19] = "10000000000000000000000000001";
	(*map)->grid[20] = "10000000000000000000000000001";
	(*map)->grid[21] = "10000000000000000000000000001";
	(*map)->grid[22] = "10000000000000000000000000001";
	(*map)->grid[23] = "10000000000000000000000000001";
	(*map)->grid[24] = "10000000000000000000000000001";
	(*map)->grid[25] = "10000000000000000000000000001";
	(*map)->grid[26] = "11111111111111111111111111111";
	
	(*map)->num_cols = 29;
	(*map)->num_rows = 27;
	(*map)->f = ft_malloc(4 * sizeof(int *));
	(*map)->c = ft_malloc(4 * sizeof(int *));
	(*map)->f[0] = 0;
	(*map)->f[1] = 0;
	(*map)->f[2] = 0;
	(*map)->f[3] = 0;
	(*map)->c[0] = 0;
	(*map)->c[1] = 0;
	(*map)->c[2] = 0;
	(*map)->c[3] = 0;
	(*map)->PlayerRotationStart = 'N';
	(*map)->playerX = 11;
	(*map)->playerY = 5;

	

}
int main(int ac, char **av)
{
	t_map *map;
	mlx_t *mlx;
	mlx_image_t *img;

	test(&map);
	if (ac == 2) // 1 bach ntester bla parsing
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
