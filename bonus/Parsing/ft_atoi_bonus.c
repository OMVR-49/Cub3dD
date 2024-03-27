/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:46:04 by sacharai          #+#    #+#             */
/*   Updated: 2024/03/26 20:54:24 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d_bonus.h"

int     ft_atoi(const char *str)
{
        int     i;
        int     s;
        int     r;

        s = 1;
        i = 0;
        r = 0;
        while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
                i++;
        if (str[i] == '-' || str[i] == '+')
        {
                if (str[i] == '-')
                        s *= -1;
                i++;
        }
        while (str[i] && (str[i] >= '0' && str[i] <= '9'))
        {
                r = r * 10 + str[i] - '0';
                i++;
        }
        return (r * s);
}