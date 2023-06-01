/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:24:48 by almelo            #+#    #+#             */
/*   Updated: 2023/05/30 17:29:55 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main( int argc, char **argv)
{
	t_data	data;

	if (!verification_main(argv, argc, &data))
		return (0);

/*
	data.mlx = mlx_init();
	load_textures(&data);
	load_colors(&data);
	set_player_position(&data);
	set_player_direction(&data);

	data.win = mlx_new_window(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
	set_hooks(&data);
	mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_loop(data.mlx);
	free_main(&data); */
	return (0);
}
