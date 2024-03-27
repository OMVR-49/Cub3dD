/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_txt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:08:45 by sacharai          #+#    #+#             */
/*   Updated: 2024/03/27 22:24:20 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	delete_txt(t_config test, mlx_t *mlx)
{
	mlx_delete_texture(test.texture_no);
	mlx_delete_texture(test.texture_so);
	mlx_delete_texture(test.texture_we);
	mlx_delete_texture(test.texture_ea);
	mlx_terminate(mlx);
}
