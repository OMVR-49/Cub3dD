/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grbg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 20:08:42 by sacharai          #+#    #+#             */
/*   Updated: 2024/03/27 22:53:01 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

t_collector	**ft_collector(void)
{
	static t_collector	*colctr;

	return (&colctr);
}

t_collector	*ft_lstnew_clctr(void *lst)
{
	t_collector	*new;

	new = malloc(sizeof(t_collector));
	if (!new)
		return (0);
	ft_lstadd_back_clctr(ft_collector(), new);
	new->ptr = lst;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_clctr(t_collector **lst, t_collector *new)
{
	t_collector	*last;

	if (!lst)
		return ;
	last = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
	new->next = NULL;
}
