/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_help3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:40:13 by sacharai          #+#    #+#             */
/*   Updated: 2024/03/27 06:39:17 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	validate_map_chars(char **map, int i, int j)
{
	if (map[i][j] != '1' && map[i][j] != '0' &&
		map[i][j] != 'N' && map[i][j] != 'S' && map[i][j]
			!= 'W' && map[i][j] != 'E' && map[i][j] != ' ')
		ft_error(7);
}

t_ply	*player_position(char **map, int *p_find, t_ply *player, t_point *p)
{
	if (map[p->i][p->j] == 'N'
		|| map[p->i][p->j] == 'S' || map[p->i][p->j] == 'W'
		|| map[p->i][p->j] == 'E')
	{
		player->x = p->i;
		player->y = p->j;
		player->direction = map[p->i][p->j];
		if (*p_find == 1)
			ft_error(6);
		*p_find = 1;
	}
	return (player);
}

t_ply	*check_map_valid_char(char **map)
{
	t_point	p;
	int		p_find;
	t_ply	*player;

	player = ft_malloc(sizeof(t_ply));
	p.i = 0;
	p_find = 0;
	while (map[p.i])
	{
		p.j = 0;
		while (map[p.i][p.j])
		{
			validate_map_chars(map, p.i, p.j);
			player = player_position(map, &p_find, player, &p);
			p.j++;
		}
		p.i++;
	}
	if (p_find == 0)
		ft_error(9);
	return (player);
}

int	calculate_max_size_line(char **map)
{
	int	max_size_line;
	int	i;

	i = 0;
	max_size_line = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > max_size_line)
			max_size_line = ft_strlen(map[i]);
		i++;
	}
	return (max_size_line);
}

char	**create_helpmap(char **map, int max_size_line, int num_rows)
{
	char	**helpmap;
	int		j;
	int		k;

	j = 0;
	helpmap = ft_malloc(sizeof(char *) * (num_rows + 1));
	while (j < num_rows)
	{
		k = 0;
		helpmap[j] = ft_malloc(sizeof(char) * (max_size_line + 1));
		while (k < max_size_line)
		{
			if (k >= ft_strlen(map[j]))
				helpmap[j][k] = ' ';
			else
				helpmap[j][k] = map[j][k];
			k++;
		}
		helpmap[j][k] = '\0';
		j++;
	}
	return (helpmap);
}
