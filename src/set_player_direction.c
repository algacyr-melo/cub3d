/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player_direction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 04:54:35 by almelo            #+#    #+#             */
/*   Updated: 2023/05/30 04:55:23 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	handle_NO(t_data *data)
{
	data->dir_x = -1;
	data->dir_y = 0;
	data->plane_x = 0;
	data->plane_y = 0.66;
	return ;
}

static void	handle_SO(t_data *data)
{
	data->dir_x = 1;
	data->dir_y = 0;
	data->plane_x = 0;
	data->plane_y = -0.66;
	return ;
}

static void	handle_EA(t_data *data)
{
	data->dir_x = 0;
	data->dir_y = -1;
	data->plane_x = -0.66;
	data->plane_y = 0;
	return ;
}

static void	handle_WE(t_data *data)
{
	data->dir_x = 0;
	data->dir_y = 1;
	data->plane_x = 0.66;
	data->plane_y = 0;
	return ;
}

void	set_player_direction(t_data *data)
{
	if (data->spawn_orientation == 'N')
		handle_NO(data);
	else if (data->spawn_orientation == 'S')
		handle_SO(data);
	else if (data->spawn_orientation == 'E')
		handle_EA(data);
	else if (data->spawn_orientation == 'W')
		handle_WE(data);
	return ;
}
