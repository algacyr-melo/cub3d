/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:55:33 by almelo            #+#    #+#             */
/*   Updated: 2023/05/18 15:23:27 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MAP_WIDTH	24
#define MAP_HEIGHT	24

extern int world_map[MAP_WIDTH][MAP_HEIGHT];

int	world_map[MAP_WIDTH][MAP_HEIGHT] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

#include "cub3d.h"

int	render_next_frame(t_data *data)
{
	t_img	img;
	t_line	vline;

	img.img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	set_image_data(&img);
	vline.x = 0;
	while (vline.x < SCREEN_WIDTH)
	{
		//calculate ray position and direction
		double	camera_x = 2 * vline.x / (double)(SCREEN_WIDTH - 1); //x-coordinate in camera space
		double	ray_dir_x = data->dir_x + data->plane_x * camera_x;
		double	ray_dir_y = data->dir_y + data->plane_y * camera_x;

		//which box of the map we're in
		int		map_x = (int)data->pos_x;
		int		map_y = (int)data->pos_y;

		//length of ray from current position to next x or y-side
		double	side_dist_x;
		double	side_dist_y;

		//length of ray from one x or y-side to next x or y-side
		double	delta_dist_x = (ray_dir_x == 0) ? INFINITY : fabs(1 / ray_dir_x);
		double	delta_dist_y = (ray_dir_y == 0) ? INFINITY : fabs(1 / ray_dir_y);
		double	perp_wall_dist;

		//what direction to step in x or y-direction (either +1 or -1)
		int		step_x;
		int		step_y;

		int		hit = 0; //was there a wall hit?
		int		side; //was a NS or a EW wall hit?

		//calculate step and initial side_dist
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (data->pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data->pos_x) * delta_dist_x;
		}
		if(ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (data->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data->pos_y) * delta_dist_y;
		}

		//perform DDA
		while (hit == 0)
		{
			if(side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			//check if ray has hit a wall
			if (world_map[map_x][map_y] > 0) hit = 1;
		}

		//calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if (side == 0)	perp_wall_dist = (side_dist_x - delta_dist_x);
		else			perp_wall_dist = (side_dist_y - delta_dist_y);

		//calculate height of line to draw on screen
		vline.height = (int)(SCREEN_HEIGHT / perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		vline.y_start = -vline.height / 2 + SCREEN_HEIGHT / 2;
		if (vline.y_start < 0)
			vline.y_start = 0;

		vline.y_end = vline.height / 2 + SCREEN_HEIGHT / 2;
		if (vline.y_end >= SCREEN_HEIGHT)
			vline.y_end = SCREEN_HEIGHT - 1;

		//choose wall color
		switch(world_map[map_x][map_y])
		{
			case 1: vline.color = 0xFF0000; break; //red
			case 2: vline.color = 0x00FF00; break; //green
			case 3: vline.color = 0x0000FF; break; //blue
			case 4: vline.color = 0xFFFFFF; break; //white
			default: vline.color = 0xFFFF00; break; //yellow
		}

		if (side == 1) { vline.color = vline.color / 2; }

		draw_vertical_line(&img, &vline);
		vline.x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
	mlx_destroy_image(data->mlx, img.img);
	return (0);
}
