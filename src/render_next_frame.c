/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:55:33 by almelo            #+#    #+#             */
/*   Updated: 2023/05/22 21:31:06 by psydenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	render_next_frame(t_data *data)
{
	t_img		img;
	t_line		vline;
	uint32_t	screen_buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	t_img		tex;
	int			tex_width;
	int			tex_height;

	//load texture
	tex.img = mlx_xpm_file_to_image(data->mlx, "./textures/redbrick.xpm", &tex_width, &tex_height);
	set_image_data(&tex);

	//create blank frame
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
		double	delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
		double	delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
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
		int pitch = 100;	
		//calculate lowest and highest pixel to fill in current stripe

		vline.y_start = -vline.height / 2 + SCREEN_HEIGHT / 2 + pitch;
		if (vline.y_start < 0)
			vline.y_start = 0;

		vline.y_end = vline.height / 2 + SCREEN_HEIGHT / 2 + pitch;
		if (vline.y_end >= SCREEN_HEIGHT)
			vline.y_end = SCREEN_HEIGHT - 1;

		//texturing calculations
	//	int texNum = world_map[map_x][map_y] - 1; // subtracted from it so that texture 0 can be used!

		//calculate value of wall_x
		double	wall_x; //where exactly the wall was hit
		if (side == 0)	
			wall_x = data->pos_y + perp_wall_dist * ray_dir_y;
		else			
			wall_x = data->pos_x + perp_wall_dist * ray_dir_x;
		wall_x -= floor((wall_x));

		//x coordinate on the texture
		int	tex_x = (int)(wall_x * (double)(tex_width));
		if (side == 0 && ray_dir_x > 0)	tex_x = tex_width - tex_x - 1;
		if (side == 1 && ray_dir_y < 0)	tex_x = tex_width - tex_x - 1;

		//how much to increase the texture coordinate per screen pixel
		double	step = 1.0 * tex_height / vline.height;

		//starting texture coordinate
		double	tex_pos = (vline.y_start - pitch - SCREEN_HEIGHT / 2 + vline.height / 2) * step;
		for (int y = vline.y_start; y < vline.y_end; y++)
		{
			//cast the texture coordinate to integer, and mask with (tex_width - 1) in case of overflow
			int	tex_y = (int)tex_pos & (tex_height - 1);
			tex_pos += step;
			//int	color = *(uint32_t *)(tex.addr + tex_height * (tex_x + tex_y));
			int	color = *(uint32_t *)(tex.addr + (tex_x * (tex.bits_per_pixel / 8) + (tex_y * tex.line_length)));

			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(side == 1)	color = (color >> 1) & 8355711;
			screen_buffer[y][vline.x] = color;
		}
		vline.x++;
	}
	draw_next_frame(&img, screen_buffer);
	for(int y = 0; y < SCREEN_HEIGHT; y++) for(int x = 0; x < SCREEN_WIDTH; x++) screen_buffer[y][x] = 0; //clear the buffer instead of cls()
	mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
	mlx_destroy_image(data->mlx, img.img);
	mlx_destroy_image(data->mlx, tex.img);
	return (0);
}
