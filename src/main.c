/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:24:48 by almelo            #+#    #+#             */
/*   Updated: 2023/05/24 03:54:32 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main( int argc, char **argv)
{
	t_data	data;

	if (!verification_main(argv, argc, &data))
			return (0);

	(void)argc;
	(void)argv;
	//initial player position and orientation that should be loaded from.cub
	data.pos_x = 22, data.pos_y = 12; //x and y start position
	data.dir_x = -1, data.dir_y = 0; //initial direction vector
	data.plane_x = 0, data.plane_y = 0.66; //the 2d raycaster version of camera plane
	
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
	set_hooks(&data);
	mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_loop(data.mlx);
	return (0);
}
