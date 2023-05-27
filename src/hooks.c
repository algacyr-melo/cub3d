/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:38:11 by almelo            #+#    #+#             */
/*   Updated: 2023/05/27 04:53:42 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
	double				old_dir_x;
	double				old_plane_x;
	t_dir_vector		dir;
	t_plane_vector		plane;

	// both camera direction and camera plane must be rotated
	dir.x = data->dir_x;
	dir.y = data->dir_y;
	old_dir_x = dir.x;
    data->dir_x = dir.x * cos(ROT_SPEED) - dir.y * sin(ROT_SPEED);
    data->dir_y = old_dir_x * sin(ROT_SPEED) + dir.y * cos(ROT_SPEED);

	plane.x = data->plane_x;
	plane.y = data->plane_y;
    old_plane_x = plane.x;
    data->plane_x = plane.x * cos(ROT_SPEED) - plane.y * sin(ROT_SPEED);
    data->plane_y = old_plane_x * sin(ROT_SPEED) + plane.y * cos(ROT_SPEED);
	return ;
}

void	rotate_right(t_data *data)
{
	double				old_dir_x;
	double				old_plane_x;
	t_dir_vector		dir;
	t_plane_vector		plane;

	// both camera direction and camera plane must be rotated
	dir.x = data->dir_x;
	dir.y = data->dir_y;
	old_dir_x = dir.x;
    data->dir_x = dir.x * cos(-ROT_SPEED) - dir.y * sin(-ROT_SPEED);
    data->dir_y = old_dir_x * sin(-ROT_SPEED) + dir.y * cos(-ROT_SPEED);

	plane.x = data->plane_x;
	plane.y = data->plane_y;
	old_plane_x = plane.x;
    data->plane_x = plane.x * cos(-ROT_SPEED) - plane.y * sin(-ROT_SPEED);
    data->plane_y = old_plane_x * sin(-ROT_SPEED) + plane.y * cos(-ROT_SPEED);
	return ;
}

void	move_forward(t_data *data)
{
	char	**world_map;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;

	world_map = data->map.world_map;
	pos_x = data->pos_x;
	pos_y = data->pos_y;
	dir_x = data->dir_x;
	dir_y = data->dir_y;

	// move forward if no wall in front of you
	if(world_map[(int)(pos_x + dir_x * MOVE_SPEED)][(int)pos_y] != '1')
		data->pos_x += dir_x * MOVE_SPEED;
	if(world_map[(int)pos_x][(int)(pos_y + dir_y * MOVE_SPEED)] != '1')
		data->pos_y += dir_y * MOVE_SPEED;
	return ;
}

void	move_backwards(t_data *data)
{
	char	**world_map;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;

	world_map = data->map.world_map;
	pos_x = data->pos_x;
	pos_y = data->pos_y;
	dir_x = data->dir_x;
	dir_y = data->dir_y;

	//move backwards if no wall behind you
	if(world_map[(int)(pos_x - dir_x * MOVE_SPEED)][(int)pos_y] != '1')
		data->pos_x -= dir_x * MOVE_SPEED;
	if(world_map[(int)pos_x][(int)(pos_y - dir_y * MOVE_SPEED)] != '1')
		data->pos_y -= dir_y * MOVE_SPEED;
	return ;
}

void	move_right(t_data *data)
{
	char	**world_map;
	double	pos_x;
	double	pos_y;
	double	plane_x;
	double	plane_y;

	world_map = data->map.world_map;
	pos_x = data->pos_x;
	pos_y = data->pos_y;
	plane_x = data->plane_x;
	plane_y = data->plane_y;

	if(world_map[(int)(pos_x + plane_x * MOVE_SPEED)][(int)pos_y] != '1')
		data->pos_x += plane_x * MOVE_SPEED;
	if(world_map[(int)pos_x][(int)(pos_y + plane_y * MOVE_SPEED)] != '1')
		data->pos_y += plane_y * MOVE_SPEED;
	return ;
}

void	move_left(t_data *data)
{
	char	**world_map;
	double	pos_x;
	double	pos_y;
	double	plane_x;
	double	plane_y;

	world_map = data->map.world_map;
	pos_x = data->pos_x;
	pos_y = data->pos_y;
	plane_x = data->plane_x;
	plane_y = data->plane_y;

	if(world_map[(int)(pos_x - plane_x * MOVE_SPEED)][(int)pos_y] != '1')
		data->pos_x -= plane_x * MOVE_SPEED;
	if(world_map[(int)pos_x][(int)(pos_y - plane_y * MOVE_SPEED)] != '1')
		data->pos_y -= plane_y * MOVE_SPEED;
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
