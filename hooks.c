/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:38:11 by almelo            #+#    #+#             */
/*   Updated: 2023/05/22 16:04:42 by psydenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

#ifdef __linux__
    #include "hooks_linux.h"
#elif defined(__APPLE__)
    #include "hooks_mac.h"
#endif



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

void	move_forward(t_data *data)
{
	// move forward if no wall in front of you
	if(world_map[(int)(data->pos_x + data->dir_x * MOVE_SPEED)][(int)(data->pos_y)] == 0)
		data->pos_x += data->dir_x * MOVE_SPEED;
	if(world_map[(int)(data->pos_x)][(int)(data->pos_y + data->pos_x * MOVE_SPEED)] == 0)
		data->pos_y += data->dir_y * MOVE_SPEED;
	return ;
}

void	move_backwards(t_data *data)
{
	//move backwards if no wall behind you
	if(world_map[(int)(data->pos_x - data->dir_x * MOVE_SPEED)][(int)(data->pos_y)] == 0)
		data->pos_x -= data->dir_x * MOVE_SPEED;
	if(world_map[(int)(data->pos_x)][(int)(data->pos_y - data->dir_y * MOVE_SPEED)] == 0)
		data->pos_y -= data->dir_y * MOVE_SPEED;
	return ;
}

void	move_right(t_data *data)
{
	if(world_map[(int)(data->pos_x + data->plane_x * MOVE_SPEED)][(int)(data->pos_y)] == 0)
		data->pos_x += data->plane_x * MOVE_SPEED;
	if(world_map[(int)(data->pos_x)][(int)(data->pos_y + data->plane_y * MOVE_SPEED)] == 0)
		data->pos_y += data->plane_y * MOVE_SPEED;
	return ;
}

void	move_left(t_data *data)
{
	if(world_map[(int)(data->pos_x - data->plane_x * MOVE_SPEED)][(int)(data->pos_y)] == 0)
		data->pos_x -= data->plane_x * MOVE_SPEED;
	if(world_map[(int)(data->pos_x)][(int)(data->pos_y - data->plane_y * MOVE_SPEED)] == 0)
		data->pos_y -= data->plane_y * MOVE_SPEED;
	return ;
}

int	handle_keydown(int keycode, t_data *data)
{
	if (keycode == W)
		move_forward(data);
	if (keycode == S)
		move_backwards(data);
	if (keycode == A)
		move_left(data);
	if (keycode == D)
		move_right(data);
	if (keycode == LEFT_ARROW)
		rotate_left(data);
	if (keycode == RIGHT_ARROW)
		rotate_right(data);
	if (keycode == ESC)
		handle_exit(data);
	return (0);
}

void	set_hooks(t_data *data)
{
	mlx_hook(data->win, ON_KEYDOWN, 1L << 0, handle_keydown, data);
	mlx_hook(data->win, ON_DESTROY, 1L << 2, handle_destroy, data);
}
