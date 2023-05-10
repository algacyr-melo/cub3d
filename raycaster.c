/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:24:48 by almelo            #+#    #+#             */
/*   Updated: 2023/05/10 17:01:20 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

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

#include <mlx.h>
#include <math.h>
#include <stdlib.h>

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_vertical_line(t_data *data, int x, int start, int end, int color)
{
	int	y_offset = 0;
	while ( y_offset < (end - start))
	{
		my_mlx_pixel_put(data, x, start + y_offset, color);
		y_offset++;
	}
}

int	main( int /*argc*/, char */*argv*/[])
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	double	pos_x = 22, pos_y = 12; //x and y start position
	double	dir_x = -1, dir_y = 0; //initial direction vector
	double	plane_x = 0, plane_y = 0.66; //the 2d raycaster version of camera plane

	//double	time = 0;
	//double	old_time = 0;
	mlx = mlx_init();
	mlx_win = mlx_new_window
	(
		mlx,
	 	SCREEN_WIDTH,
	 	SCREEN_HEIGHT,
	 	"My first raycaster!"
	 );
	(void)mlx_win;
	img.img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr
	(
		img.img,
		&img.bits_per_pixel,
		&img.line_length,
		&img.endian
	);
	while (42)
	{
		int	x = 0;
		while ( x < SCREEN_WIDTH )
		{
			//calculate ray position and direction
			double	camera_x = 2 * x / (double)(SCREEN_WIDTH - 1); //x-coordinate in camera space
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
			int	line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);

			//calculate lowest and highest pixel to fill in current stripe
			int	draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
			if (draw_start < 0)	draw_start = 0;
			int	draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
			if (draw_end >= SCREEN_HEIGHT)	draw_end = SCREEN_HEIGHT - 1;

			//choose wall color
			int	color;
			switch(map[map_x][map_y])
			{
				case 1: color = 0xFF0000; break; //red
				case 2: color = 0x00FF00; break; //green
				case 3: color = 0x0000FF; break; //blue
				case 4: color = 0xFFFFFF; break; //white
				default: color = 0xFFFF00; break; //yellow
			}

			if (side == 1) { color = color / 2; }

			draw_vertical_line(&img, x, draw_start, draw_end, color);
			x++;
		}
		mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	}
	mlx_loop(mlx);
	return (0);
}
