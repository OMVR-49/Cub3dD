/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:39:27 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/27 11:43:13 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	ft_error(int x)
{
	if (x == 1)
		ft_message("Wrong number of arguments", 1);
	else if (x == 2)
		ft_message("Wrong file extension", 2);
	else if (x == 3)
		ft_message("File not found", 3);
	else if (x == 4)
		ft_message("Wrong number of arguments", 4);
	else if (x == 5)
		ft_message("missing key", 5);
	else if (x == 6)
		ft_message("multiple player", 6);
	else if (x == 7)
		ft_message("invalid char in map", 7);
	else if (x == 8)
		ft_message("invalid color", 8);
	else if (x == 9)
		ft_message("no player", 9);
	else if (x == 10)
		ft_message("invalid map", 10);
	else if (x == 11)
		ft_message("no map", 11);
	else if (x == 15)
		ft_message("empty line in the middle of the map", 15);
}

void	check_images(t_map *map)
{
	t_start	*tmp;
	int		fd;

	tmp = map->head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "F") != 0 && ft_strcmp(tmp->key, "C") != 0)
		{
			fd = open(tmp->value, O_RDONLY);
			if (fd == -1)
				ft_error(3);
			else
				close(fd);
		}
		tmp = tmp->next;
	}
}

void	fill_headers(t_map *map)
{
	t_start	*tmp;

	tmp = map->head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "NO"))
			map->no = tmp->value;
		else if (!ft_strcmp(tmp->key, "SO"))
			map->so = tmp->value;
		else if (!ft_strcmp(tmp->key, "WE"))
			map->we = tmp->value;
		else if (!ft_strcmp(tmp->key, "EA"))
			map->ea = tmp->value;
		tmp = tmp->next;
	}
}

int	main(int ac, char **av)
{
	mlx_image_t	*img;
	t_map		*map;
	mlx_t		*mlx;

	map = NULL;
	mlx = NULL;
	if (ac == 2)
	{
		map = parsing(ac, av);
		fill_headers(map);
		check_images(map);
		if (map)
		{
			mlx_set_setting(0, true);
			mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
			img = mlx_new_image(mlx, WIDTH, HEIGHT);
			raycasting(map, mlx, img);
		}
	}
	else
		ft_error(1);
	mlx_terminate(mlx);
}
