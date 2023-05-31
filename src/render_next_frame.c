/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:55:33 by almelo            #+#    #+#             */
/*   Updated: 2023/05/31 02:03:02 by almelo           ###   ########.fr       */
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

int	render_next_frame(t_data *data)
{
	t_raycaster	rc;
	t_frame		frame;

	//create blank frame
	frame.img.img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	set_image_data(&frame.img);

	rc.screen_x = 0;
	while (rc.screen_x < SCREEN_WIDTH)
	{
		calculate_ray_position(&rc);
		calculate_ray_direction(&rc, data);

		//which box of the map we're in
		rc.map_x = (int)data->pos_x;
		rc.map_y = (int)data->pos_y;

		//length of ray from one x or y-side to next x or y-side
		rc.delta_dist_x = (rc.ray_dir_x == 0) ? 1e30 : fabs(1 / rc.ray_dir_x);
		rc.delta_dist_y = (rc.ray_dir_y == 0) ? 1e30 : fabs(1 / rc.ray_dir_y);

		calculate_step(&rc);
		calculate_side_dist(&rc, data);
		dda_loop(&rc, data);
		set_wall_texture(&rc, data, &frame);
		calculate_camera_dist(&rc);
		calculate_wall_data(&rc);

		// Texturing calculations

		//calculate value of wall_x
		double	wall_x; //where exactly the wall was hit
		if (rc.side == 0)	
			wall_x = data->pos_y + rc.perp_wall_dist * rc.ray_dir_y;
		else			
			wall_x = data->pos_x + rc.perp_wall_dist * rc.ray_dir_x;
		wall_x -= floor((wall_x));

		//x coordinate on the texture
		int	tex_x = (int)(wall_x * (double)(data->tex_width));
		if (rc.side == 0 && rc.ray_dir_x > 0)	tex_x = data->tex_width - tex_x - 1;
		if (rc.side == 1 && rc.ray_dir_y < 0)	tex_x = data->tex_width - tex_x - 1;

		//how much to increase the texture coordinate per screen pixel
		double	step = 1.0 * data->tex_height / rc.wall_height;

		// Draw ceil
		for (int y = 0; y < rc.wall_top; y++)
			frame.buffer[y][rc.screen_x] = data->color_ceil;

		// Draw floor
		for (int y = rc.wall_bottom; y < SCREEN_HEIGHT; y++)
			frame.buffer[y][rc.screen_x] = data->color_floor;

		//starting texture coordinate
		double	tex_pos = (rc.wall_top - SCREEN_HEIGHT / 2 + rc.wall_height / 2) * step;
		for (int y = rc.wall_top; y < rc.wall_bottom; y++)
		{
			//cast the texture coordinate to integer, and mask with (tex_width - 1) in case of overflow
			int	tex_y = (int)tex_pos & (data->tex_height - 1);
			tex_pos += step;
			int	color = *(uint32_t *)(frame.wall_tex.addr + (tex_x * (frame.wall_tex.bits_per_pixel / 8) + (tex_y * frame.wall_tex.line_length)));

			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(rc.side == 0)	color = (color >> 1) & 8355711;
			frame.buffer[y][rc.screen_x] = color;
		}
		rc.screen_x++;
	}
	draw_next_frame(&frame.img, frame.buffer);
	for(int y = 0; y < SCREEN_HEIGHT; y++) for(int x = 0; x < SCREEN_WIDTH; x++) frame.buffer[y][x] = 0; //clear the buffer instead of cls()
	mlx_put_image_to_window(data->mlx, data->win, frame.img.img, 0, 0);
	mlx_destroy_image(data->mlx, frame.img.img);
	return (0);
}
