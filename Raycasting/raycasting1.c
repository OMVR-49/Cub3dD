/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 00:35:41 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/22 11:19:31 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void initialize(t_config *config, t_map **map, mlx_t *mlx, mlx_image_t *img)
{
	config->player.x = 0; //ps: search for x placement of the config in the array
	config->player.y = 0; //ps: search for y placement of the config in the array
	config->player.Raduis = 3;
	config->player.RotationSpeed = (double)(3 * (M_PI / 180));
	config->player.TurnDirection = 0;
	config->player.WalkDirection = 0;
	config->player.RotationAngle = Pi/3;
	config->player.MovementSpeed = 1;
	config->map = (*map);
	config->player.x = ((*map)->playerX * TileSize) + (TileSize / 2);
	config->player.y = ((*map)->playerY * TileSize) + (TileSize / 2);
	config->mlx = mlx;
	config->img = img;
}

void grid(mlx_image_t *img, int tileX , int tileY, uint32_t tileColor)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x <= TileSize)
	{
		y = 0;
		while(y <= TileSize) 
		{
			mlx_put_pixel(img, y + tileX, x + tileY, tileColor);
			if (x == 0 || y == 0 )
				mlx_put_pixel(img, y + tileX , x + tileY, 0x000000FF);
			y++;
		}
		x++;
	}
}

void setup_map(t_config *config)
{
	uint32_t tileColor;
	int i;
	int j;
	int x;
	int y;

	i = 0;
	y = 0;
	while (y < config->map->num_rows)
	{
		j = 0;
		x = 0;
		while (x < config->map->num_cols)
		{
			if(config->map->grid[y][x] == 1)
				tileColor = 0x00008BFF;
			else
				tileColor = 0xFFFFFFFF;
			grid(config->img, i, j, tileColor);
			j += TileSize;
			x++;
		}
		i += TileSize;
		y++;
	}
}

void	setup_player(t_config *config)
{
	mlx_put_pixel(config->img, config->player.x, config->player.y ,0xFF2E2EFF);
}
void	setup_line(t_config *config)
{
	int x;
	int y;
	x = config->player.x;
	y = config->player.y;
	draw_line(config->img, x, y, x + cos(config->player.RotationAngle) * 20, y + sin(config->player.RotationAngle) * 20);
	mlx_image_to_window(config->mlx, config->img, 0, 0);
}

void	setup_fov(t_config *config)
{
// int step;
// int dx = x2 - x1;
// int dy = y2 - y1;
// int Xinc;
// int Yinc;
// int i;

// if (abs(dx) > abs(dy))
// 		step = abs(dx);
// else
// 		step = abs(dy);
// Xinc = dx/step;
// Yinc = dy/step;
// i = 0;
// while (i < step)
// {
// 		mlx_put_pixel(config->img, x, y, color);
// 		x = x1 + Xinc;
// 		y = y1 + Yinc;
// 		i++;
// }
}

bool	KeyPressed1(t_config *config)
{
	if (mlx_is_key_down(config->mlx, MLX_KEY_D))
	{
		return (true);
	}
	if (mlx_is_key_down(config->mlx, MLX_KEY_A))
	{
		return (true);
	}
	if (mlx_is_key_down(config->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(config->mlx);
	}
	return (false);
}
int	KeyPressed(t_config *config)
{
	int i;

	i = 0;
	if (mlx_is_key_down(config->mlx, MLX_KEY_S))
	{
		config->player.WalkDirection = -1 + (0 * i++);
		printf("---------------\n");
	}
	if (mlx_is_key_down(config->mlx, MLX_KEY_W))
		config->player.WalkDirection = 1 + (0 * i++);
	if (mlx_is_key_down(config->mlx, MLX_KEY_RIGHT))
		config->player.TurnDirection = 1 + (0 * i++);
	if (mlx_is_key_down(config->mlx, MLX_KEY_LEFT))
		config->player.TurnDirection = -1 + (0 * i++);
	if (KeyPressed1(config))
		return(true);
	return(i);
}
int isWall(t_config *config, double x, double y)
{
	int gridIndexX;
	int gridIndexY;

	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
		return (true);
	gridIndexX = floor(x / TileSize);
	gridIndexY = floor(y / TileSize);
	if (config->map->grid[gridIndexX][gridIndexY] != 0)
		return(true);
	else
		return(false);

}

void UpdatePlayerPos(t_config *config)
{
	int moveStep;
	double new_xpos;
	double new_ypos;

	config->player.RotationAngle += config->player.TurnDirection * config->player.RotationSpeed;
	moveStep = config->player.WalkDirection * config->player.MovementSpeed;
	new_xpos = config->player.x + cos(config->player.RotationAngle) * moveStep;
	new_ypos = config->player.y + sin(config->player.RotationAngle) * moveStep;
	if (!isWall(config, new_xpos, new_ypos))
	{
		config->player.x = new_xpos;
		config->player.y = new_ypos;
	}
}

void Update(t_config *config)
{
	config->img = mlx_new_image(config->mlx, WIDTH, HEIGHT);
	UpdatePlayerPos(config);
	setup_map(config);
	setup_player(config);
	setup_line(config);
	mlx_image_to_window(config->mlx, config->img, 0, 0);
}

void	Hook(void *param) // if necessery typecast the void parameter u understand
{
	t_config *config;

	config = (struct s_config *)param;
	if (KeyPressed(config))
	{
		mlx_delete_image(config->mlx, config->img);
		Update(config);
		config->player.TurnDirection = 0;
		config->player.WalkDirection = 0;
	}
}

void raycasting(t_map *map, mlx_t *mlx, mlx_image_t *img)
{
	t_config *config;

	config = ft_malloc(sizeof (t_config));
	initialize(config, &map , mlx, img);
	setup_map(config);
	setup_player(config);
	setup_line(config);
	// setup_fov(config);
	
	// lkhedma kamla hna t genera l merra llwla mn be3d teb9a 3ndk function we7da li 
	// hia Update teb9a t3awd t genere based on l keys wl values li ghadi ytbedlo
	mlx_loop_hook(config->mlx, &Hook, config);
	mlx_loop(mlx);
}
