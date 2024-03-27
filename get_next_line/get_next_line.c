/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 06:07:36 by sacharai          #+#    #+#             */
/*   Updated: 2024/03/27 20:38:16 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*line_by_line(int fd, char *saved)
{
	char	*buff;
	int		ref;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	buff[0] = '\0';
	ref = 1;
	while (ref != 0 && !ft_strchr(buff, '\n'))
	{
		ref = read(fd, buff, BUFFER_SIZE);
		if (ref == -1)
		{
			free(buff);
			free(saved);
			return (NULL);
		}
		buff[ref] = '\0';
		saved = ft_strjoin(saved, buff);
	}
	free(buff);
	return (saved);
}

char	*ft_line(char *saved)
{
	int		i;
	char	*line;

	i = 0;
	if (!saved[0])
		return (0);
	while (saved[i] != '\n' && saved[i])
		i++;
	line = (char *)malloc((sizeof(char) * i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (saved[i] != '\n' && saved[i])
	{
		line[i] = saved[i];
		i++;
	}
	if (saved[i] == '\n')
	{
		line[i] = saved[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_saved(char *saved)
{
	int		i;
	int		c;
	char	*next;

	i = 0;
	c = 0;
	while (saved[i] != '\n' && saved[i])
		i++;
	if (!saved[i])
	{
		free (saved);
		return (NULL);
	}
	next = malloc(sizeof(char) * ft_strlen(saved) - i + 1);
	if (!next)
		return (NULL);
	i++;
	while (saved[i])
		next[c++] = saved[i++];
	next[c] = '\0';
	free(saved);
	return (next);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*saved;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	saved = line_by_line(fd, saved);
	if (!saved)
		return (NULL);
	line = ft_line(saved);
	saved = ft_saved(saved);
	return (line);
}
