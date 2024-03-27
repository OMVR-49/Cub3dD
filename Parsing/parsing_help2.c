/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_help2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:18:38 by sacharai          #+#    #+#             */
/*   Updated: 2024/03/27 13:56:52 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	len_char(char *str, char c)
{
	int	i;
	int	len;	

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			len++;
		i++;
	}
	return (len);
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

void	validate_color_input(char **tmprgb)
{
	if (check_number(tmprgb[0]) == 0 || check_number(tmprgb[1]) == 0
		|| check_number(tmprgb[2]) == 0)
		ft_error(8);
	if (ft_atoi(tmprgb[0]) < 0 || ft_atoi(tmprgb[0]) > 255
		|| ft_atoi(tmprgb[1]) < 0 || ft_atoi(tmprgb[1]) > 255
		|| ft_atoi(tmprgb[2]) < 0 || ft_atoi(tmprgb[2]) > 255)
		ft_error(8);
}

int	help_parse_color(char *str)
{
	int		j;
	int		rgb;
	char	**tmprgb;

	j = 0;
	if (len_char(str, ',') != 2)
		ft_error(8);
	tmprgb = ft_split(str, ',');
	validate_color_input(tmprgb);
	rgb = calculate_rgb(tmprgb);
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
	int		*rgb;

	rgb = ft_malloc(sizeof(int) * 2);
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
