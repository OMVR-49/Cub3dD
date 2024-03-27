/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:43:37 by sacharai          #+#    #+#             */
/*   Updated: 2024/03/27 11:36:44 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	ft_message(char *message, int x)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	exit(x);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char const *s, int fd)
{
	if (s != NULL)
	{
		while (*s != '\0')
		{
			write(fd, s, 1);
			s++;
		}
	}
}
