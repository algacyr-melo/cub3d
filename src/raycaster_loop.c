/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 02:21:22 by almelo            #+#    #+#             */
/*   Updated: 2023/06/01 02:46:04 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	calculate_ray_position(t_raycaster *rc)
{
	rc->camera_x = 2 * rc->screen_x / (double)(SCREEN_WIDTH) - 1;
	return;
}

void	calculate_ray_direction(t_raycaster *rc, t_data *data)
{
	rc->ray_dir_x = data->dir_x + data->plane_x * rc->camera_x;
	rc->ray_dir_y = data->dir_y + data->plane_y * rc->camera_x;
	return;
}

void	calculate_step(t_raycaster *rc)
{
	if (rc->ray_dir_x < 0)
		rc->step_x = -1;
	else
		rc->step_x = 1;
	if (rc->ray_dir_y < 0)
		rc->step_y = -1;
	else
		rc->step_y = 1;
	return ;
}

void	calculate_side_dist(t_raycaster *rc, t_data *data)
{
	if (rc->ray_dir_x < 0)
		rc->side_dist_x = (data->pos_x - rc->map_x) * rc->delta_dist_x;
	else
		rc->side_dist_x = (rc->map_x + 1.0 - data->pos_x) * rc->delta_dist_x;
	if(rc->ray_dir_y < 0)
		rc->side_dist_y = (data->pos_y - rc->map_y) * rc->delta_dist_y;
	else
		rc->side_dist_y = (rc->map_y + 1.0 - data->pos_y) * rc->delta_dist_y;
	return ;
}

void	dda_loop(t_raycaster *rc, t_data *data)
{
	rc->hit = 0;
	while (rc->hit == 0)
	{
		if(rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (data->map.world_map[rc->map_x][rc->map_y] == '1')
			rc->hit = 1;
	}
	return ;
}

void	set_wall_texture(t_raycaster *rc, t_data *data, t_frame *frame)
{
	if (rc->side == 0)
	{
		if (rc->map_x > data->pos_x)
			frame->wall_tex = data->tex_SO;
		else
			frame->wall_tex = data->tex_NO;
	}
	else
	{
		if (rc->map_y > data->pos_y)
			frame->wall_tex = data->tex_WE;
		else
			frame->wall_tex = data->tex_EA;
	}
	return ;
}

void	calculate_camera_dist(t_raycaster *rc)
{
	if (rc->side == 0)
		rc->perp_wall_dist = (rc->side_dist_x - rc->delta_dist_x);
	else
		rc->perp_wall_dist = (rc->side_dist_y - rc->delta_dist_y);
	return ;
}

void	calculate_wall_data(t_raycaster *rc)
{
	rc->wall_height = (int)(SCREEN_HEIGHT / rc->perp_wall_dist);

	rc->wall_top = -rc->wall_height / 2 + SCREEN_HEIGHT / 2;
	if (rc->wall_top < 0 || rc->wall_top > SCREEN_HEIGHT)
		rc->wall_top = 0;

	rc->wall_bottom = rc->wall_height / 2 + SCREEN_HEIGHT / 2;
	if (rc->wall_bottom >= SCREEN_HEIGHT || rc->wall_bottom < 0)
		rc->wall_bottom = SCREEN_HEIGHT - 1;
	return ;
}

static void	set_delta_dist(t_raycaster *rc)
{
	if (rc->ray_dir_x == 0)
		rc->delta_dist_x = INFINITY;
	else
		rc->delta_dist_x = fabs(1 / rc->ray_dir_x);
	if (rc->ray_dir_y == 0)
		rc->delta_dist_y = INFINITY;
	else
		rc->delta_dist_y = fabs(1 / rc->ray_dir_y);
	return ;
}

void	raycaster_loop(t_raycaster *rc, t_data *data, t_frame *frame)
{
	rc->screen_x = 0;
	while (rc->screen_x < SCREEN_WIDTH)
	{
		calculate_ray_position(rc);
		calculate_ray_direction(rc, data);
		rc->map_x = (int)data->pos_x;
		rc->map_y = (int)data->pos_y;
		set_delta_dist(rc);
		calculate_step(rc);
		calculate_side_dist(rc, data);
		dda_loop(rc, data);
		set_wall_texture(rc, data, frame);
		calculate_camera_dist(rc);
		calculate_wall_data(rc);
		set_wall_pixel_x(rc, data);
		buffer_ceil_v_line(rc, data, frame);
		buffer_floor_v_line(rc, data, frame);
		set_texture_x(rc, data);
		buffer_wall_v_line(rc, data, frame);
		rc->screen_x++;
	}
	return ;
}
