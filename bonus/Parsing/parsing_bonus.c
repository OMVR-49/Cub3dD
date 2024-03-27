/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:33:36 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/27 01:22:45 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d_bonus.h"

t_start *parse_head(int fd, char **line,int i,t_start *head)
{
    char *tmp;
    char **str;

    while (*line)
    {
        tmp = *line;
        *line = ft_strtrim(*line, "\n");
        free(tmp);
        i = 0;
        if(ft_strlen(*line) != 0)
        {
            str = ft_split(*line, ' ');
            if(check_if_exist(head, str[0]) == 6)
                break;
            while (str[i])
                i++;
            if (i != 2)
                ft_error(4);
            insert_node(&head, str[0], str[1] , 0);
        }
        free(*line);
        *line = get_next_line(fd);
    }
    return head;
}

t_start *parse_map(int fd, char **line)
{
    t_start *map = NULL;
    char *tmp;
    int is_new_line = 0;

    while(*line)
    {
        tmp = *line;
        *line = ft_strtrim(*line, "\n");
        free(tmp);
        if(ft_strlen(*line)== 0)
            is_new_line = 1;
        if(is_new_line == 1 && ft_strlen(*line) != 0)
            ft_error(15);
        insert_node(&map, ft_strdup("map"), *line,1);
        *line = get_next_line(fd);
    }
    return map;
}

char **convert_map_to_array(t_start *map)
{
    int Maplen = list_length(map);
    char **maparray = ft_malloc(sizeof(char *) * (Maplen + 1));
    int i = 0;
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
    return maparray;
}

t_map *initialize_map(t_start *head, t_start *map, int *rgb)
{
    t_map *mapp;
    char **maparray = convert_map_to_array(map);
    t_ply *help = check_map_valid_char(maparray);
    mapp = valid_map(maparray);
    mapp->player_rotation_start = help->direction;
    mapp->player_x = help->y;
    mapp->player_y = help->x;
    mapp->f = rgb[1];
    mapp->c = rgb[0];
    mapp->head = head;
    free(help);
    free(rgb);
    return (mapp);
}

t_map *parsing(int ac, char **av)
{
    t_type h;

    if(ft_strlen(av[1]) < 4)
        ft_error(2);
    h.tmp = ft_substr(av[1],ft_strlen(av[1])-4,4);
    if (ft_strncmp(h.tmp, ".cub", 4) != 0)
        ft_error(2);
    free(h.tmp);
    h.fd = open(av[1], O_RDONLY);
    if (h.fd == -1)
        ft_error(3);
    h.line = get_next_line(h.fd);
    h.head = parse_head(h.fd, &h.line,0,NULL);
    h.rgb = parse_color(h.head);
    while(ft_strlen(h.line) == 0)
    {
        free(h.line);
        h.line = get_next_line(h.fd);
        if(h.line == NULL)
            ft_error(14);
    }
    h.map = parse_map(h.fd, &h.line);
    h.mapp = initialize_map(h.head, h.map, h.rgb);
    close(h.fd);
    return (h.mapp);
}
