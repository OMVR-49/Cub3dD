/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_help2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:18:38 by sacharai          #+#    #+#             */
/*   Updated: 2024/03/26 23:05:22 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	len_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	check_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	help_parse_color(char *str)
{
	int		i;
	int		j;
	int		rgb;
	char	**tmprgb;

	i = 0;
	j = 0;
	tmprgb = ft_split(str, ',');
	if (len_char(tmprgb[0], ',') != 2)
		ft_error(8);
	if (check_number(tmprgb[0]) == 0 || check_number(tmprgb[1]) == 0
		|| check_number(tmprgb[2]) == 0)
		ft_error(8);
	if (ft_atoi(tmprgb[0]) < 0 || ft_atoi(tmprgb[0]) > 255 || ft_atoi(tmprgb[1]) < 0 || ft_atoi(tmprgb[1]) > 255 || ft_atoi(tmprgb[2]) < 0 || ft_atoi(tmprgb[2]) > 255)
		ft_error(8);
	rgb = ft_atoi(tmprgb[0]) * 65536
		+ ft_atoi(tmprgb[1]) * 256 + ft_atoi(tmprgb[2]);
	while (tmprgb[j])
	{
		free(tmprgb[j]);
		j++;
	}
	free(tmprgb);
	return (rgb);
}

int	*parse_color(t_start *head)
{
	t_start	*tmp;
	char	*tmprgb;
	int		*rgb;

	rgb = malloc(sizeof(int) * 2);
	tmp = head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "C"))
			rgb[0] = help_parse_color(tmp->value);
		else if (!ft_strcmp(tmp->key, "F"))
			rgb[1] = help_parse_color(tmp->value);
		tmp = tmp->next;
	}
	return (rgb);
}
