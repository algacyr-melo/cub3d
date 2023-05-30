/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:38:12 by almelo            #+#    #+#             */
/*   Updated: 2023/05/30 02:09:02 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	load_texture_NO(t_data *data)
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

static void	load_texture_SO(t_data *data)
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

static void	load_texture_WE(t_data *data)
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

static void	load_texture_EA(t_data *data)
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

void	load_textures(t_data *data)
{
	load_texture_NO(data);
	load_texture_SO(data);
	load_texture_WE(data);
	load_texture_EA(data);
	return ;
}
