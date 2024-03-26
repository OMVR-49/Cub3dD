/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:26:01 by sacharai          #+#    #+#             */
/*   Updated: 2024/03/26 23:05:40 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

t_start	*create_node(char *key, char *value)
{
	t_start	*node;

	node = malloc(sizeof(t_start));
	node->key = key;
	node->value = value;
	node->flag = 0;
	node->rgb_num = NULL;
	node->next = NULL;
	return (node);
}


void	validate_key(char *key, int flag)
{
	int		i;
	char	**table;

	table = ft_split("NO SO WE EA F C", ' ');
	if (flag == 0)
	{
		i = 0;
		flag = 0;
		while (table[i])
		{
			if (ft_strcmp(table[i], key) == 0)
				flag++;
			free(table[i]);
			i++;
		}
		free(table);
		if (flag == 0)
			ft_error(5);
	}
}

void	insert_node(t_start **head, char *key, char *value, int flag)
{
	t_start	*new_node;
	t_start	*tmp;

	validate_key(key, flag);

	tmp = *head;
	new_node = create_node(key, value);
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}
