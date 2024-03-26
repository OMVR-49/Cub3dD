/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:33:36 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/26 03:12:50 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int check_if_exist(t_start *head, char *key)
{
	t_start *tmp;
	char **value;
	int i;
	i = 0;
	tmp = head;
	
	while(tmp)
	{
		i++;
		tmp = tmp->next;
	}
	if(i == 6)
		return 6;
	tmp = head;
	i = 0;
	while (tmp)
	{
		if (key== NULL || ft_strcmp(tmp->key, key) == 0)
			ft_error(5); // error 5 missing key
		tmp = tmp->next;
		i++;
	}
	return (i);
}


t_start	*create_node(char *key, char *value)
{
	t_start	*node;

	node = malloc(sizeof(t_start));
	node->key = key;
	node->value = value;
	node->flag = 0;
	node->rgb_num = NULL;
	node->next = NULL;
	return (node);
}

void	insert_node(t_start **head, char *key, char *value, int flag)
{
	t_start	*new_node;
	t_start	*tmp = *head;
	int i;
	char **table;
	table = ft_split("NO SO WE EA F C", ' ');
	if( flag == 0)
	{
		i = 0;
		flag = 0;
		while(table[i])
		{
			if(ft_strcmp(table[i], key) == 0)
				flag++;
			free(table[i]);
			i++;
		}
		free(table);
		if(flag == 0)
			ft_error(19); // error 19 is invalid key
	}
	new_node = create_node(key, value);
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}
int linkedListLength(t_start *head)
{
	t_start *current = head;
	int count = 0;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return count;
}

t_ply* check_map_valid_char(char **map)
{
	int i;
	int j;
	int isplayerfind = 0;
	t_ply *player;

	player = malloc(sizeof(t_ply));
	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'W' && map[i][j] != 'E' && map[i][j] != ' ')
				ft_error(7); // error 7 is invalid char in map
			if(map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
			{
				player->x = i;
				player->y = j;
				player->direction = map[i][j];
				if(isplayerfind == 1)
					ft_error(6); // error 6 is multiple player
				isplayerfind = 1;
			}
			j++;
		}
		i++;
	}
	if(isplayerfind == 0)
		ft_error(6); // error 9 is no player
	return player;
}

void chack_spaces(char **map)
{
	int i = 0;
	int j = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] != ' ' && map[i][j] != '1')
			{
				if(map[i][j + 1] == ' ' || map[i][j - 1] == ' ' || map[i + 1][j] == ' ' || map[i - 1][j] == ' ')
					ft_error(10);
			}
			j++;
		}
		i++;
	}

}

t_map * valid_map(char **map)
{
	int max_size_line = 0;
	t_map *mapp;
	int i = 0;
	int k = 0;
	
	mapp = ft_malloc(sizeof(t_map));
	while(map[i])
	{
		if(ft_strlen(map[i]) > max_size_line)
			max_size_line = ft_strlen(map[i]);
		i++;
	}
	mapp->num_rows = i;
	mapp->num_cols = max_size_line;
	char **helpmap = malloc(sizeof(char *) * (i + 1));
	int j = 0;
	while(j < i)
{
    k = 0;
    helpmap[j] = malloc(sizeof(char) * (max_size_line + 1));
    while(k < max_size_line)
    {
        if(k >= ft_strlen(map[j]))
            helpmap[j][k] = ' ';
        else
            helpmap[j][k] = map[j][k];
        k++;
    }
    helpmap[j][k] = '\0';
    j++;
}
	char **newmap = malloc(sizeof(char *) * (i + 3));
	newmap[0] = malloc(sizeof(char) * (max_size_line + 3));
	j = 0;
	while(j < max_size_line + 2)
		newmap[0][j++] = ' ';
	newmap[0][j] = '\0';
	j = 1;
	while(j < i + 1)
	{
		k = 0;
		newmap[j] = malloc(sizeof(char) * (max_size_line + 3));
		while(k < max_size_line + 2)
		{
			if(k == 0 || k > ft_strlen(map[j - 1]))
				newmap[j][k] = ' ';
			else
				newmap[j][k] = map[j - 1][k - 1];
			k++;
		}
		newmap[j][k] = '\0';
		j++;
	}
	newmap[j] = malloc(sizeof(char) * (max_size_line + 3));
	j = 0;
	while(j < max_size_line  + 2)
		newmap[i + 1][j++] = ' ';
	newmap[i + 1][j] = '\0';
	newmap[i + 2] = NULL;
	chack_spaces(newmap);
	mapp->grid = helpmap;
	return mapp;
}
int len_char(char *str,char c)
{
	int i;

	i = 0;
	while(str[i] && str[i] != c)
		i++;
	return (i);
}
int check_number(char *str)
{
	int i;
	i = 0;
	while(str[i])
	{
		if(str[i] < '0' || str[i] > '9')
			return 0; // error 8 is invalid color
		i++;
	}
	return 1;
}
int help_parse_color(char *str)
{
	int i;
	int j;
	int rgb;
	char **tmprgb;
	i = 0;
	j = 0;
	tmprgb = ft_split(str, ',');
	if(len_char(tmprgb[0], ',') != 2)
		ft_error(17); // error 8 is invalid color
	if(check_number(tmprgb[0]) == 0 || check_number(tmprgb[1]) == 0 || check_number(tmprgb[2]) == 0)
		ft_error(17); // error 8 is invalid color
	if(ft_atoi(tmprgb[0]) < 0 || ft_atoi(tmprgb[0]) > 255 || ft_atoi(tmprgb[1]) < 0 || ft_atoi(tmprgb[1]) > 255 || ft_atoi(tmprgb[2]) < 0 || ft_atoi(tmprgb[2]) > 255)
		ft_error(17); // error 8 is invalid color
	rgb = ft_atoi(tmprgb[0]) * 65536 + ft_atoi(tmprgb[1]) * 256 + ft_atoi(tmprgb[2]);
	while(tmprgb[j])
	{
		free(tmprgb[j]);
		j++;
	}
	free(tmprgb);
	return rgb;
}
int *parse_color(t_start *head)
{
	t_start *tmp;
	char *tmprgb;
	int *rgb;
	
	rgb = malloc(sizeof(int) * 2);
	tmp = head;
	while(tmp)
	{
		if (!ft_strcmp(tmp->key, "C") )
			rgb[0] = help_parse_color(tmp->value);
		else if (!ft_strcmp(tmp->key, "F"))
			rgb[1] = help_parse_color(tmp->value);
		tmp =tmp->next;
	}
	return rgb;
}

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
    if (ac != 2)
        ft_error(1);
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
				ft_error(4);
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
			ft_error(14); // error 14 is no map
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
			ft_error(15); // error 15 is empty line in the middle of the map
		}
		insert_node(&map, ft_strdup("map"), line,1);
		line = get_next_line(fd);
	}
	int Maplen = linkedListLength(map);
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
	mapp->PlayerRotationStart = help->direction;
	mapp->playerX = help->y;
	mapp->playerY = help->x;
	printf("playerX %d\n", mapp->playerX);
	printf("playerY %d\n", mapp->playerY);
	mapp->f = rgb[1];
	mapp->c = rgb[0];
	free(help);
	free(rgb);
    close(fd);
	return mapp;
}
