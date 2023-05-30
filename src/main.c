/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:24:48 by almelo            #+#    #+#             */
/*   Updated: 2023/05/30 01:31:56 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	load_texture_NO(t_data *data)
{
	data->tex_NO.img = mlx_xpm_file_to_image
		(
			data->mlx,
			data->map.path_NO,
			&data->tex_width,
			&data->tex_height
		);
	set_image_data(&data->tex_NO);
	return ;
}

void	load_texture_SO(t_data *data)
{
	data->tex_SO.img = mlx_xpm_file_to_image
		(
			data->mlx,
			data->map.path_SO,
			&data->tex_width,
			&data->tex_height
		);
	set_image_data(&data->tex_SO);
	return ;
}

void	load_texture_WE(t_data *data)
{
	data->tex_WE.img = mlx_xpm_file_to_image
		(
			data->mlx,
			data->map.path_WE,
			&data->tex_width,
			&data->tex_height
		);
	set_image_data(&data->tex_WE);
	return ;
}

void	load_texture_EA(t_data *data)
{
	data->tex_EA.img = mlx_xpm_file_to_image
		(
			data->mlx,
			data->map.path_EA,
			&data->tex_width,
			&data->tex_height
		);
	set_image_data(&data->tex_EA);
	return ;
}

int	main( int argc, char **argv)
{
	t_data	data;

	if (!verification_main(argv, argc, &data))
		return (0);

	//initial player position and orientation that should be loaded from.cub
	data.pos_x = 4, data.pos_y = 4; //x and y start position
	data.dir_x = -1, data.dir_y = 0; //initial direction vector
	data.plane_x = 0, data.plane_y = 0.66; //the 2d raycaster version of camera plane

	data.mlx = mlx_init();

	// Load textures
	load_texture_NO(&data);
	load_texture_SO(&data);
	load_texture_WE(&data);
	load_texture_EA(&data);

	data.win = mlx_new_window(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
	set_hooks(&data);
	mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_loop(data.mlx);
	free_main(&data);
	return (0);
}
