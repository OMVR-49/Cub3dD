/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 00:35:41 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/23 05:50:30 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void initialize(t_config *config, t_map **map)
{
	config->player.x = 0; //ps: search for x placement of the config in the array
	config->player.y = 0; //ps: search for y placement of the config in the array
	config->player.Raduis = 3;
	config->player.RotationSpeed = (double)(5 * (M_PI / 180));
	config->player.TurnDirection = 0;
	config->player.WalkDirection = 0;
	config->player.RotationAngle = Pi/3;
	config->player.MovementSpeed = 2;
	config->map = (*map);
	config->player.x = ((*map)->playerX * (HEIGHT / config->map->num_rows)) + (HEIGHT / config->map->num_rows / 2);
	config->player.y = ((*map)->playerY * ((WIDTH / config->map->num_cols))) + (WIDTH / config->map->num_rows / 2);
	config->mlx = mlx;
	config->img = img;
}

void grid(t_config *config, int tileX , int tileY, uint32_t tileColor)
{
	int x;
	int y;

	x = 0;
	y = 0;
	int xx = WIDTH / config->map->num_cols; //check
	int yy = HEIGHT / config->map->num_rows; // check
	while (x <= xx)
	{
		y = 0;
		while(y <= yy)
		{
			mlx_put_pixel(config->img, y + tileX, x + tileY, tileColor);
			if (x == 0 || y == 0 )
				mlx_put_pixel(config->img, y + tileX , x + tileY, 0x000000FF);
			y++;
		}
		x++;
	}
}

void setup_map(t_config *config, mlx_t *mlx, mlx_image_t *img)
{
	uint32_t tileColor;
	int i;
	int j;
	int x;
	int y;

	i = 0;
	y = 0;
	while (y < 4) // check
	{
		j = 0;
		x = 0;
		while (x < 4) // check
		{
			if(config->map->grid[y][x] == 1)
				tileColor = 0x00008BFF;
			else
				tileColor = 0xFFFFFFFF;
			grid(config, i, j, tileColor);
			j += HEIGHT / config->map->num_rows; // check
			x++;
		}
		i += HEIGHT / config->map->num_rows; // check 
		y++;
	}
	mlx_image_to_window(mlx, img, 0, 0);
}

void	setup_player(t_config *config, mlx_t *mlx, mlx_image_t *img)
{
	mlx_put_pixel(config->img, config->player.x, config->player.y ,0xFF2E2EFF);
}
void	setup_line(t_config *config)
{
	int x;
	int y;
	x = config->player.x;
	y = config->player.y;
	draw_line(config, x + cos(config->player.RotationAngle) * 50, y + sin(config->player.RotationAngle) * 50, 0x7f11e099);
	mlx_image_to_window(config->mlx, config->img, 0, 0);
}

void	dda(t_config *config)
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
		return (true);
	if (mlx_is_key_down(config->mlx, MLX_KEY_A))
		return (true);
	if (mlx_is_key_down(config->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(config->mlx);
	return (false);
}
int	KeyPressed(t_config *config)
{
	int i;

	i = 0;
	if (mlx_is_key_down(config->mlx, MLX_KEY_S))
		config->player.WalkDirection = -1 + (0 * i++);
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
	gridIndexX = floor(x / (HEIGHT / config->map->num_rows));
	gridIndexY = floor(y / (WIDTH / config->map->num_cols));
	if (config->map->grid[gridIndexX][gridIndexY] != 0)
		return(true);
	else
		return(false);

}

void	keyPressed(void *param) // if necessery typecast the void parameter u understand
{
	mlx_key_data_t keyCode;
	t_config *config;

void	castAllRays(t_config *config)
{
	int i;
	double rayAngle;
	double rayEndX;
	double rayEndY;

	i = 0;
	rayAngle = config->player.RotationAngle - (FOV_ANGLE / 2);
	while(i < 1) //rdha NUM_RAY rak ghir ttebe3 dakchi li kaydir pikuma bach tefhem
	{
		rayEndX = config->player.x + cos(rayAngle) * 50;
		rayEndY = config->player.y + sin(rayAngle) * 50;
		config->rays[i].rayAngle = rayAngle;
        config->rays[i].endX = rayEndX;
        config->rays[i].endY = rayEndY;
		draw_line(config, rayEndX, rayEndY, 0x7f11e011);
		rayAngle += (FOV_ANGLE / NUM_RAYS);
		i++;
	}
	mlx_image_to_window(config->mlx, config->img, 0, 0);
}
void	setup_fov(t_config *config)
{
	castAllRays(config);
	
}

void Update(t_config *config)
{
	config->img = mlx_new_image(config->mlx, WIDTH, HEIGHT);
	UpdatePlayerPos(config);
	setup_map(config);
	setup_player(config);
	setup_line(config);
	setup_fov(config);
	mlx_image_to_window(config->mlx, config->img, 0, 0);
}

void	player_movement(t_config *config, mlx_t *mlx, mlx_image_t *img)
{
	mlx_key_data_t keys;

	setup_player(config, mlx, img);
	mlx_loop_hook(mlx, &keyPressed, config);
}

int raycasting(t_map *map, mlx_t *mlx, mlx_image_t *img)
{
	t_config *config;

	config = ft_malloc(sizeof (t_config));
	initialize(config, &map , mlx, img);
	setup_map(config);
	setup_player(config);
	setup_line(config);
	setup_fov(config);
	
	// lkhedma kamla hna t genera l merra llwla mn be3d teb9a 3ndk function we7da li 
	// hia Update teb9a t3awd t genere based on l keys wl values li ghadi ytbedlo
	mlx_loop_hook(config->mlx, &Hook, config);
	mlx_loop(mlx);
}
