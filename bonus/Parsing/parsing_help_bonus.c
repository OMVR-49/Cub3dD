/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_help_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:56:04 by sacharai          #+#    #+#             */
/*   Updated: 2024/03/27 01:12:25 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d_bonus.h"

int     ft_strcmp(const char *s1, const char *s2)
{
        size_t                  i;
        unsigned char   *ps1;
        unsigned char   *ps2;

        ps1 = (unsigned char *)s1;
        ps2 = (unsigned char *)s2;
        i = 0;
        while ((ps1[i] || ps2[i]) && (ps1[i] == ps2[i]))
                        i++;
        return (ps1[i] - ps2[i]);
}

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

char    *ft_strdup(const char *s)
{
        char    *str;
        int             i;

        i = 0;
        str = (char *)ft_malloc(sizeof(char) * (ft_strlen(s) + 1));
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
                str = ft_malloc(sizeof(char) * ((lens - start) + 1));
        else
                str = ft_malloc(sizeof(char) * (len + 1));
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

size_t  ft_strlcpy(char *dst, const char *src, size_t size)
{
        size_t  i;
        size_t  l;

        l = ft_strlen(src);
        i = 0;
        if (size != 0)
        {
                while (src[i] && i < size - 1)
                {
                        dst[i] = src[i];
                        i++;
                }
                dst[i] = '\0';
        }
        return (l);
}

char    *ft_strtrim(char *s1, char *set)
{
        size_t  i;
        char    *str;
        size_t  ls1;

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