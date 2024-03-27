/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:33:36 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/26 23:56:16 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

t_map *parsing(int ac, char **av)
{
    int fd;
    char *line;
    char *tmp;
	char **str;
	int i;
	int *rgb;
	t_map *mapp;
	

	i = 0;
    if(ft_strlen(av[1]) < 4)
        ft_error(2);
    tmp = ft_substr(av[1],ft_strlen(av[1])-4,4);
    if (ft_strncmp(tmp, ".cub", 4) != 0)
    {
        free(tmp);
        ft_error(2);
    }
    free(tmp);
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
        ft_error(3);
    line = get_next_line(fd);
	t_start *head = NULL;
	while (line)
	{
		tmp = line;
		line = ft_strtrim(line, "\n");
		free(tmp);
		i = 0;
		if(ft_strlen(line) != 0)
		{
			str = ft_split(line, ' ');
			if(check_if_exist(head, str[0]) == 6)
				break;
			while (str[i])
				i++;
			if (i != 2)
			{
				printf("line %s i= %d\n", line, i);
				ft_error(4);
			}
			insert_node(&head, str[0], str[1] , 0);
		}
		free(line);
		line = get_next_line(fd);
	}
	rgb = parse_color(head);
	t_start *map = NULL;
	while(ft_strlen(line) == 0)
	{
		free(line);
		line = get_next_line(fd);
		if(line == NULL)
			ft_error(14);
	}
	int is_new_line = 0;
	while(line)
	{
		tmp = line;
		line = ft_strtrim(line, "\n");
		free(tmp);
		if(ft_strlen(line)== 0)
			is_new_line = 1;
		if(is_new_line == 1 && ft_strlen(line) != 0)
		{
			printf("line %s\n", line);
			ft_error(15);
		}
		insert_node(&map, ft_strdup("map"), line,1);
		line = get_next_line(fd);
	}
	int Maplen = list_length(map);
	char **maparray = malloc(sizeof(char *) * (Maplen + 1));
	i = 0;
	t_start *tmpmap = NULL;
	while(map)
	{
		maparray[i] = map->value;
		i++;
		tmpmap = map;
		map = map->next;
		free(tmpmap->key);
		free(tmpmap);
	}
	maparray[i] = NULL;
	t_ply *help = check_map_valid_char(maparray);
	mapp = valid_map(maparray);
	mapp->player_rotation_start = help->direction;
	mapp->player_x = help->y;
	mapp->player_y = help->x;
	mapp->f = rgb[1];
	mapp->c = rgb[0];
	free(help);
	free(rgb);
	close(fd);
	return (mapp);
}
