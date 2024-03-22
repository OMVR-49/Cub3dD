/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:56:04 by sacharai          #+#    #+#             */
/*   Updated: 2024/03/22 15:56:25 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int     ft_strncmp(const char *s1, const char *s2, size_t n)
{
        size_t                  i;
        unsigned char   *ps1;
        unsigned char   *ps2;

        ps1 = (unsigned char *)s1;
        ps2 = (unsigned char *)s2;
        i = 0;
        if (n == 0)
                return (0);
        while ((ps1[i] || ps2[i]) && (ps1[i] == ps2[i]) && (i < n - 1))
                        i++;
        return (ps1[i] - ps2[i]);
}