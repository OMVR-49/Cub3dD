/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_help1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 20:56:50 by sacharai          #+#    #+#             */
/*   Updated: 2024/03/27 01:10:41 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

char	*ft_strtrim(char *s1, char *set)
{
	size_t	i;
	char	*str;
	size_t	ls1;

	if (!s1)
		return (NULL);
	str = 0;
	if (s1 != 0 && set != 0)
	{
		i = 0;
		ls1 = ft_strlen(s1);
		while (s1[i] && ft_strchr(set, s1[i]) != 0)
			i++;
		if (i == ls1)
			return (ft_strdup(""));
		while (s1[ls1 - 1] && ft_strchr(set, s1[ls1 - 1]) != 0 && ls1 > i)
			ls1--;
		str = (char *)ft_malloc(sizeof(char) * (ls1 - i + 1));
		if (!str)
			return (NULL);
		if (str)
			ft_strlcpy (str, &s1[i], ls1 - i + 1);
	}
	return (str);
}

int	check_if_exist(t_start *head, char *key)
{
	t_start	*tmp;
	char	**value;
	int		i;

	i = 0;
	tmp = head;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	if (i == 6)
		return (6);
	tmp = head;
	i = 0;
	while (tmp)
	{
		if (key == NULL || ft_strcmp(tmp->key, key) == 0)
			ft_error(5);
		tmp = tmp->next;
		i++;
	}
	return (i);
}

int	list_length(t_start *head)
{
	t_start	*current;
	int		count;

	count = 0;
	current = head;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	chack_spaces(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != ' ' && map[i][j] != '1')
			{
				if (map[i][j + 1] == ' ' || map[i][j - 1] == ' '
					|| map[i + 1][j] == ' ' || map[i - 1][j] == ' ')
					ft_error(10);
			}
			j++;
		}
		i++;
	}
}
