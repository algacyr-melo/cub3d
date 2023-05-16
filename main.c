/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:24:48 by almelo            #+#    #+#             */
/*   Updated: 2023/05/16 16:56:17 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

int	map[MAP_WIDTH][MAP_HEIGHT] =
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

int	main( int /*argc*/, char */*argv*/[])
{
	t_mlx	mlx;
	t_img	img;
	t_line	line;

	double	pos_x = 22, pos_y = 12; //x and y start position
	double	dir_x = -1, dir_y = 0; //initial direction vector
	double	plane_x = 0, plane_y = 0.66; //the 2d raycaster version of camera plane

	//double	time = 0;
	//double	old_time = 0;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
	set_hooks(&mlx);
	while (42)
	{
		img.img = mlx_new_image(mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
		set_image_data(&img);
		line.x = 0;
		while ( line.x < SCREEN_WIDTH )
		{
			//calculate ray position and direction
			double	camera_x = 2 * line.x / (double)(SCREEN_WIDTH - 1); //x-coordinate in camera space
			double	ray_dir_x = dir_x + plane_x * camera_x;
			double	ray_dir_y = dir_y + plane_y * camera_x;

			//which box of the map we're in
			int		map_x = (int)pos_x;
			int		map_y = (int)pos_y;

			//length of ray from current position to next x or y-side
			double	side_dist_x;
			double	side_dist_y;

			//length of ray from one x or y-side to next x or y-side
			double	delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
			double	delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
			double	perp_wall_dist;

			//what direction to step in x or y-direction (either +1 or -1)
			int	step_x;
			int	step_y;

			int	hit = 0; //was there a wall hit?
			int	side; //was a NS or a EW wall hit?
		
			//calculate step and initial side_dist
			if (ray_dir_x < 0)
			{
				step_x = -1;
				side_dist_x = (pos_x - map_x) * delta_dist_x;
			}
			else
			{
				step_x = 1;
				side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
			}
			if (ray_dir_y < 0)
			{
				step_y = -1;
				side_dist_y = (pos_y - map_y) * delta_dist_y;
			}
			else
			{
				step_y = 1;
				side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
			}

			//perform DDA
			while (hit == 0)
			{
				//jump to next map square, either in x-direction, or in y-direction
				if (side_dist_x < side_dist_y)
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
				if (map[map_x][map_y] > 0) hit = 1;
			}

			//calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
			if (side == 0)	perp_wall_dist = (side_dist_x - delta_dist_x);
			else			perp_wall_dist = (side_dist_y - delta_dist_y);

			//calculate height of line to draw on screen
			line.height = (int)(SCREEN_HEIGHT / perp_wall_dist);

			//calculate lowest and highest pixel to fill in current stripe
			line.y_start = -line.height / 2 + SCREEN_HEIGHT / 2;
			if (line.y_start < 0)
				line.y_start = 0;

			line.y_end = line.height / 2 + SCREEN_HEIGHT / 2;
			if (line.y_end >= SCREEN_HEIGHT)
				line.y_end = SCREEN_HEIGHT - 1;

			//choose wall color
			switch(map[map_x][map_y])
			{
				case 1: line.color = 0xFF0000; break; //red
				case 2: line.color = 0x00FF00; break; //green
				case 3: line.color = 0x0000FF; break; //blue
				case 4: line.color = 0xFFFFFF; break; //white
				default: line.color = 0xFFFF00; break; //yellow
			}

			if (side == 1) { line.color = line.color / 2; }

			draw_vertical_line(&img, &line);
			line.x++;
		}
		mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
		mlx_destroy_image(mlx.mlx, img.img);
		mlx_loop(mlx.mlx);
	}
	return (0);
}
