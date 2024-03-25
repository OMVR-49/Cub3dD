/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 22:04:21 by ojebbari          #+#    #+#             */
/*   Updated: 2024/03/21 03:37:01 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../MLX42/include/MLX42/MLX42.h"
#include <math.h>

typedef struct s_vars {
    mlx_t *mlx;
    float angle;
    int x_head, y_head; // The fixed "head" of the line around which it rotates
} t_vars;

void draw_rotated_line(t_vars *vars) {
    int length = 100; // Length of the line
    float rad = vars->angle * (M_PI / 180); // Convert angle to radians

    // Calculate the tail's position based on the angle
    int x_tail = vars->x_head - cos(rad) * length;
    int y_tail = vars->y_head - sin(rad) * length;

    // Clear the window and draw the line
    mlx_clear_window(vars->mlx);
    mlx_draw_line(vars->mlx, (mlx_point_t){x_tail, y_tail}, (mlx_point_t){vars->x_head, vars->y_head}, 0xFFFFFF);
}

void key_event(mlx_key_data_t keydata, void *param) {
    t_vars *vars = param;
    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) {
        if (keydata.key == MLX_KEY_RIGHT) {
            vars->angle += 5; // Rotate 5 degrees clockwise
        } else if (keydata.key == MLX_KEY_LEFT) {
            vars->angle -= 5; // Rotate 5 degrees counter-clockwise
        }
    }
}

void loop_hook(void *param) {
    t_vars *vars = param;
    draw_rotated_line(vars);
}

int main(void) {
    t_vars vars;
    vars.mlx = mlx_init(800, 600, "Rotation Example", false);
    if (!vars.mlx) return 1;

    vars.angle = 0;
    vars.x_head = 400; // Center of the window
    vars.y_head = 300; // Center of the window

    mlx_key_hook(vars.mlx, key_event, &vars);
    mlx_loop_hook(vars.mlx, loop_hook, &vars);
    mlx_loop(vars.mlx);

    mlx_terminate(vars.mlx);
    return 0;
}


//compile : gcc image.c -Iinclude -lglfw -L"/Users/ojebbari/.brew/opt/glfw/lib/" ../MLX42/build/libmlx42.a