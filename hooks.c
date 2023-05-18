/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:38:11 by almelo            #+#    #+#             */
/*   Updated: 2023/05/18 15:41:25 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "hooks.h"
#include <stdio.h>

void	handle_exit(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}

int	handle_destroy(t_data *data)
{
	handle_exit(data);
	return (0);
}

void	rotate_left(t_data *data)
{
	// both camera direction and camera plane must be rotated
	double oldDirX = data->dir_x;
    data->dir_x = data->dir_x * cos(ROT_SPEED) - data->dir_y * sin(ROT_SPEED);
    data->dir_y = oldDirX * sin(ROT_SPEED) + data->dir_y * cos(ROT_SPEED);

    double oldPlaneX = data->plane_x;
    data->plane_x = data->plane_x * cos(ROT_SPEED) - data->plane_y * sin(ROT_SPEED);
    data->plane_y = oldPlaneX * sin(ROT_SPEED) + data->plane_y * cos(ROT_SPEED);
	return ;
}

void	rotate_right(t_data *data)
{
	// both camera direction and camera plane must be rotated
	double oldDirX = data->dir_x;
    data->dir_x = data->dir_x * cos(-ROT_SPEED) - data->dir_y * sin(-ROT_SPEED);
    data->dir_y = oldDirX * sin(-ROT_SPEED) + data->dir_y * cos(-ROT_SPEED);

    double oldPlaneX = data->plane_x;
    data->plane_x = data->plane_x * cos(-ROT_SPEED) - data->plane_y * sin(-ROT_SPEED);
    data->plane_y = oldPlaneX * sin(-ROT_SPEED) + data->plane_y * cos(-ROT_SPEED);
	return ;
}

int	handle_keydown(int keycode, t_data *data)
{
	if (keycode == ESC)
		handle_exit(data);
	if (keycode == LEFT_ARROW)
		rotate_left(data);
	if (keycode == RIGHT_ARROW)
		rotate_right(data);
	return (0);
}

void	set_hooks(t_data *data)
{
	mlx_hook(data->win, ON_KEYDOWN, 1L << 0, handle_keydown, data);
	mlx_hook(data->win, ON_DESTROY, 1L << 2, handle_destroy, data);
}
