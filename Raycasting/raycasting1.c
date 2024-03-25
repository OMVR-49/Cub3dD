/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 00:35:41 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/25 08:50:03 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void initialize(t_config *config, t_map **map, mlx_t *mlx, mlx_image_t *img)
{
	config->map = *map;
	config->mlx = mlx;
	config->img = img;
	config->map->ratioX = WIDTH / config->map->num_cols;
	config->map->ratioY = HEIGHT / config->map->num_rows;
	config->player.x = (*map)->playerX * (config->map->ratioY) + (config->map->ratioY / 2);
	config->player.y = (*map)->playerY * (config->map->ratioX) + (config->map->ratioX / 2);
	config->player.TurnDirection = 0;
	config->player.WalkDirection = 0;
	config->player.RotationAngle =0;
	if (config->map->PlayerRotationStart == 'N')
		config->player.RotationAngle = 1.5 * M_PI;
	else if (config->map->PlayerRotationStart == 'S')
		config->player.RotationAngle = 0.5 * M_PI;
	else if (config->map->PlayerRotationStart == 'W')
		config->player.RotationAngle = M_PI;
	config->player.StrafeDirection = 0;
	config->player.MovementSpeed = 2;
	config->player.RotationSpeed = 2 * (M_PI / 180);
}

void grid(t_config *config, int tileX , int tileY, uint32_t tileColor)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x <= config->map->ratioX)
	{
		y = 0;
		while(y <= config->map->ratioY)
		{
			mlx_put_pixel(config->img, y + tileX, x + tileY, tileColor);
			if (x == 0 || y == 0 )
				mlx_put_pixel(config->img, y + tileX , x + tileY, 0x000000FF);
			y++;
		}
		x++;
	}
}

void setup_map(t_config *config)
{
	uint32_t tileColor;
	int tileY;
	int tileX;
	int x;
	int y;

	tileY = 0;
	y = 0;
	while (y < config->map->num_rows)
	{
		tileX = 0;
		x = 0;
		while (x < config->map->num_cols)
		{
			if(config->map->grid[y][x] == '1')
				tileColor = 0x2E2EFFFF;
			else if (config->map->grid[y][x] == '0')
				tileColor = 0xFFFFFFFF;
			else if(config->map->grid[y][x] == ' ')
				tileColor = 0x000000FF;
			grid(config, tileX, tileY, tileColor);
			tileX += config->map->ratioX;
			x++;
		}
		tileY += config->map->ratioY;
		y++;
}
	mlx_image_to_window(config->mlx, config->img, 0, 0);
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
	draw_line(config, x + cos(config->player.RotationAngle) * 50, y + sin(config->player.RotationAngle) * 50, 0x7f11e099);
	mlx_image_to_window(config->mlx, config->img, 0, 0);
}


bool	KeyPressed1(t_config *config)
{
	
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
	if (mlx_is_key_down(config->mlx, MLX_KEY_D))
		config->player.StrafeDirection = 1 + (0 * i++);
	if (mlx_is_key_down(config->mlx, MLX_KEY_A))
		config->player.StrafeDirection = -1 + (0 * i++);
	if (mlx_is_key_down(config->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(config->mlx);
	return(i);
}
int isWall(t_config *config, double x, double y)
{
	int mapGridIndexX;
	int mapGridIndexY;

	if (x <= 0 || x >= WIDTH || y <= 0 || y >= HEIGHT)
		return (1);
	mapGridIndexX = floor(x / (config->map->ratioX));
	mapGridIndexY = floor(y / (config->map->ratioY));
	if (mapGridIndexX < 0 || mapGridIndexX >= config->map->num_cols || mapGridIndexY < 0 || mapGridIndexY >= config->map->num_rows)
		return (1);
	if (config->map->grid[mapGridIndexY][mapGridIndexX] == '1')
		return (1);
	return (0);
}

void UpdatePlayerPos(t_config *config)
{
	double moveStep;
	double newPlayerX;
	double newPlayerY;
	double strafeStep;

	config->player.RotationAngle += config->player.TurnDirection * config->player.RotationSpeed;
	moveStep = config->player.WalkDirection * config->player.MovementSpeed;
	newPlayerX = config->player.x + cos(config->player.RotationAngle) * moveStep;
	newPlayerY = config->player.y + sin(config->player.RotationAngle) * moveStep;
	strafeStep = config->player.StrafeDirection * config->player.MovementSpeed;
	newPlayerX += cos(config->player.RotationAngle + M_PI_2) * strafeStep;
	newPlayerY += sin(config->player.RotationAngle + M_PI_2) * strafeStep;
	if (!isWall(config, newPlayerX, newPlayerY))
	{
		config->player.x = newPlayerX;
		config->player.y = newPlayerY;
	}
}
double distanceBetweenPoints(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

double normalizeAngle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}
void	whileForVert(t_config *config, t_ray *ray, double xintercept, double yintercept)
{
	while(xintercept >= 0 && xintercept <= WIDTH && yintercept >= 0 && yintercept <= HEIGHT)
	{
		double xToCheck = xintercept + (ray->isRayFacingLeft ? -1 : 0);
		double yToCheck = yintercept;
		if (ray->isRayFacingLeft)
			xToCheck--;
		if(isWall(config, xToCheck, yToCheck))
		{
			ray->foundHitVertical = true;
			ray->wallHitXV = xintercept;
			ray->wallHitYV = yintercept;
			break;
		}
		else
		{
			xintercept += ray->XincV;
			yintercept += ray->YincV;
		}
	}
}
void	castVerticalRay(t_config *config, t_ray *ray)
{
	double yintercept;
	double xintercept;
	double nextVertTouchX;
	double nextVertTouchY;

	xintercept = floor(config->player.x / (config->map->ratioY)) * ( config->map->ratioY);
	if (ray->isRayFacingRight)
		xintercept += (config->map->ratioY);
	yintercept = config->player.y + (xintercept - config->player.x) * tan(ray->rayAngle);
	ray->XincV = config->map->ratioY;
	if (ray->isRayFacingLeft)
		ray->XincV *= -1;
	ray->YincV = ray->XincV * tan(ray->rayAngle);
	if(ray->isRayFacingUp && ray->YincV > 0)
		ray->YincV *= -1;
	if(ray->isRayFacingDown && ray->YincV < 0)
		ray->YincV *= -1;
	nextVertTouchX = xintercept;
	nextVertTouchY = yintercept;
	whileForVert(config, ray, nextVertTouchX, nextVertTouchY);
}

void	whileForHorz(t_config *config, t_ray *ray, double nextHorzTouchX, double nextHorzTouchY)
{
	while(nextHorzTouchX >= 0 && nextHorzTouchX <= WIDTH && nextHorzTouchY >= 0 && nextHorzTouchY <= HEIGHT)
	{
		double xToCheck = nextHorzTouchX;
		double yToCheck = nextHorzTouchY + (ray->isRayFacingUp ? -1 : 0);
		if (ray->isRayFacingUp)
			yToCheck--;
		if(isWall(config, xToCheck, yToCheck))
		{
			ray->foundHitHorizontal = true;
			ray->wallHitXH = nextHorzTouchX;
			ray->wallHitYH = nextHorzTouchY;
			break;
		}
		else
		{
			nextHorzTouchX += ray->XincH;
			nextHorzTouchY += ray->YincH;
		}
	}
}
void	castHorizontalRay(t_config *config, t_ray *ray)
{
	double yintercept;
	double xintercept;
	double nextHorzTouchX;
	double nextHorzTouchY;

	yintercept = floor(config->player.y / (config->map->ratioX)) * (config->map->ratioX);
	if (ray->isRayFacingDown)
		yintercept += config->map->ratioX;
	xintercept = config->player.x + (yintercept - config->player.y) / tan(ray->rayAngle);
	ray->YincH = config->map->ratioX;
	if (ray->isRayFacingUp)
		ray->YincH *= -1;
	ray->XincH = ray->YincH / tan(ray->rayAngle);
	if(ray->isRayFacingLeft && ray->XincH > 0)
		ray->XincH *= -1;
	if(ray->isRayFacingRight && ray->XincH < 0)
		ray->XincH *= -1;
	nextHorzTouchX = xintercept;
	nextHorzTouchY = yintercept;
	whileForHorz(config, ray, nextHorzTouchX, nextHorzTouchY);
}

void	findClosestWallHit(t_config *config, t_ray *ray)
{
	double hDistance;
	double vDistance;

	if (ray->foundHitHorizontal)
		hDistance = distanceBetweenPoints(config->player.x, config->player.y, ray->wallHitXH, ray->wallHitYH);
	else
		hDistance = INT_MAX;
	if (ray->foundHitVertical)
		vDistance = distanceBetweenPoints(config->player.x, config->player.y, ray->wallHitXV, ray->wallHitYV);
	else
		vDistance = INT_MAX;
	if (vDistance < hDistance)
	{
		ray->wallHitX = ray->wallHitXV;
		ray->wallHitY = ray->wallHitYV;
		ray->distance = vDistance;
	}
	else
	{
		ray->wallHitX = ray->wallHitXH;
		ray->wallHitY = ray->wallHitYH;
		ray->distance = hDistance;
	}
}
void castRay(t_config *config, int stripId, double rayAngle)
{
	t_ray *ray;

	ray = &config->rays[stripId];
	ray->rayAngle = normalizeAngle(rayAngle);
	ray->isRayFacingDown = (ray->rayAngle >= 0 && ray->rayAngle <= M_PI); // zedt aw toussawi ntester
	ray->isRayFacingUp = !ray->isRayFacingDown;
	ray->isRayFacingRight = (ray->rayAngle <= 0.5 * M_PI || ray->rayAngle >= 1.5 * M_PI); // zedt aw toussawi ntester
	ray->isRayFacingLeft = !ray->isRayFacingRight;
	ray->foundHitHorizontal = false;
	ray->foundHitVertical = false;
	ray->wallHitXH = 0;
	ray->wallHitYH = 0;
	ray->wallHitXV = 0;
	ray->wallHitYV = 0;
	ray->wallHitX = 0;
	ray->wallHitY = 0;
	castHorizontalRay(config, ray);
	castVerticalRay(config, ray);
	findClosestWallHit(config, ray);
}

void	castAllRays(t_config *config)
{
	int stripId;
	double rayAngle;

	stripId = 0;
	rayAngle = config->player.RotationAngle - (FOV_ANGLE / 2);
	while(stripId < NUM_RAYS) //rdha NUM_RAY rak ghir ttebe3 dakchi li kaydir pikuma bach tefhem
	{
		castRay(config, stripId, rayAngle);
		draw_line(config,config->rays[stripId].wallHitX, config->rays[stripId].wallHitY, 0xFF0000FF); // check
		rayAngle += FOV_ANGLE / NUM_RAYS;
		stripId++;
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
	// setup_line(config);
	setup_fov(config);
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
		config->player.StrafeDirection = 0;
	}
}

void raycasting(t_map *map, mlx_t *mlx, mlx_image_t *img)
{
	t_config *config;

	config = ft_malloc(sizeof (t_config));
	initialize(config, &map , mlx, img);
	setup_map(config);
	setup_player(config);
	// setup_line(config);
	setup_fov(config);
	
	// lkhedma kamla hna t genera l merra llwla mn be3d teb9a 3ndk function we7da li 
	// hia Update teb9a t3awd t genere based on l keys wl values li ghadi ytbedlo
	mlx_loop_hook(config->mlx, &Hook, config);
	mlx_loop(mlx);
}
