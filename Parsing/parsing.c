/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:33:36 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/22 16:40:35 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void parsing(int ac, char *av, t_map *map)
{
    int fd;
    char *line;
    int i;
    int j;

    i = 0;
    j = 0;
    if (ac != 2)
        ft_error(1);
    if (ft_strncmp(av[1], ".cub", 4) != 0)
        ft_error(2);
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
        ft_error(3);
    free(line);
    close(fd);
}