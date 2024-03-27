/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_help4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 22:05:45 by sacharai          #+#    #+#             */
/*   Updated: 2024/03/27 01:52:12 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

char	*create_newmap_line(int max_size_line)
{
	char	*newmap_line;
	int		j;

	j = 0;
	newmap_line = ft_malloc(sizeof(char) * (max_size_line + 3));
	while (j < max_size_line + 2)
		newmap_line[j++] = ' ';
	newmap_line[j] = '\0';
	return (newmap_line);
}

char	*create_newmap_row(char **map, int max_size_line, int row_index)
{
	char	*newmap_row;
	int		k;

	newmap_row = ft_malloc(sizeof(char) * (max_size_line + 3));
	k = 0;
	while (k < max_size_line + 2)
	{
		if (k == 0 || k > ft_strlen(map[row_index - 1]))
			newmap_row[k] = ' ';
		else
			newmap_row[k] = map[row_index - 1][k - 1];
		k++;
	}
	newmap_row[k] = '\0';
	return (newmap_row);
}

char	**create_newmap(char **map, int max_size_line, int num_rows)
{
	char	**newmap;
	int		j;

	newmap = ft_malloc(sizeof(char *) * (num_rows + 3));
	j = 1;
	newmap[0] = create_newmap_line(max_size_line);
	while (j < num_rows + 1)
	{
		newmap[j] = create_newmap_row(map, max_size_line, j);
		j++;
	}
	newmap[j] = create_newmap_line(max_size_line);
	newmap[num_rows + 2] = NULL;
	return (newmap);
}

t_map	*valid_map(char **map)
{
	t_map	*mapp;
	int		max_size_line;
	char	**helpmap;
	char	**newmap;
	int		i;

	i = 0;
	max_size_line = calculate_max_size_line(map);
	mapp = ft_malloc(sizeof(t_map));
	while (map[i])
		i++;
	mapp->num_rows = i;
	mapp->num_cols = max_size_line;
	helpmap = create_helpmap(map, max_size_line, mapp->num_rows);
	newmap = create_newmap(map, max_size_line, mapp->num_rows);
	chack_spaces(newmap);
	mapp->grid = helpmap;
	return (mapp);
}

int	calculate_rgb(char **tmprgb)
{
	int	rgb;

	rgb = ft_atoi(tmprgb[0]) * 65536
		+ ft_atoi(tmprgb[1]) * 256 + ft_atoi(tmprgb[2]);
	return (rgb);
}
