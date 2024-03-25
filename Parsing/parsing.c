/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:33:36 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/24 02:58:08 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

// char    *ft_strchr(const char *s, int c)
// {
//         int             i;
//         char    *str;

//         i = 0;
//         str = (char *)s;
//         while (str[i] && str[i] != (char)c)
//                 i++;
//         if (str[i] == (char)c)
//                 return (str + i);
//         else
//                 return (NULL);
// }
char    *ft_strdup(const char *s)
{
        char    *str;
        int             i;

        i = 0;
        str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
        if (!str)
                return (NULL);
        while (s[i])
        {
                str[i] = s[i];
                i++;
        }
        str[i] = '\0';
        return (str);
}

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
        char                    *str;
        unsigned int    lens;
        size_t                  i;

        i = 0;
        if (!s)
                return (NULL);
        lens = ft_strlen(s);
        if (start >= lens)
                return (ft_strdup(""));
        if ((lens - start) < len)
                str = malloc(sizeof(char) * ((lens - start) + 1));
        else
                str = malloc(sizeof(char) * (len + 1));
        if (!str)
                return (NULL);
        while (i < len && s[start])
        {
                str[i] = s[start];
                i++;
                start++;
        }
        str[i] = '\0';
        return (str);
}
int check_if_exist(t_start *head, char *key)
{
	t_start *tmp;
	int i;

	i = 0;
	tmp = head;
	while (tmp)
	{
		if (key== NULL || ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
			ft_error(5);
		tmp = tmp->next;
		i++;
	}
	return (i);
}


t_start	*create_env_node(char *key, char *value)
{
	t_start	*node;

	node = malloc(sizeof(t_start));
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	insert_env_node(t_start **head, char *key, char *value)
{
	t_start	*new_node;
	t_start	*tmp = *head;

	new_node = create_env_node(key, value);
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
void check_map_valid_char(char **map)
{
	int i;
	int j;
	int isplayerfind = 0;

	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'W' && map[i][j] != 'E' && map[i][j] != ' ')
				ft_error(7);
			if(map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
			{
				if(isplayerfind == 1)
					ft_error(6);
				isplayerfind = 1;
			}
			j++;
		}
		i++;
	}
}

void valid_map(char **map)
{
	int max_size_line = 0;
	int i = 0;
	while(map[i])
	{
		if(ft_strlen(map[i]) > max_size_line)
			max_size_line = ft_strlen(map[i]);
		i++;
	}
	char **newmap = malloc(sizeof(char *) * (i + 3));
	newmap[0] = malloc(sizeof(char) * (max_size_line + 3));
	//file this line with space 
	int j = 0;
	while(j < max_size_line + 2)
		newmap[0][j++] = ' ';
	j = 1;
	int k = 0;
	while(j < i + 2)
	{
		
		newmap[j] = malloc(sizeof(char) * (max_size_line + 3));
		while(k < max_size_line + 2)
		{
			if(k == 0 || k > ft_strlen(map[j - 1]) + 1)
				newmap[j][k] = ' ';
			else
				newmap[j][k] = map[j - 1][k - 1];
			k++;
		}
		j++;
	}
	newmap[j] = malloc(sizeof(char) * (max_size_line + 3));
	j = 0;
	while(j < max_size_line + 2)
		newmap[i + 2][j++] = ' ';
	//print the new map
	j = 0;
	while(newmap[j])
	{
		printf("%s\n", newmap[j]);
		j++;
	}
	
}

void parsing(int ac, char **av)
{
    int fd;
    char *line;
    char *tmp;
	char **str;
	int i;
	

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
		i = 0;
		if(ft_strlen(line) != 1)
		{
			str = ft_split(line, ' ');
			if(check_if_exist(head, str[0]) == 6)
				break;
			while (str[i])
				i++;
			if (i != 2)
				ft_error(4);
			insert_env_node(&head, str[0], str[1]);
		}
		free(line);
		line = get_next_line(fd);
	}
	t_start *map = NULL;
	while(ft_strlen(line) == 0)
	{
		free(line);
		line = get_next_line(fd);
	}
	while(line)
	{
		insert_env_node(&map, ft_strdup("map"), line);
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
	check_map_valid_char(maparray);
	valid_map(maparray);
    close(fd);
	
}