/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psydenst <psydenst@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:03:20 by psydenst          #+#    #+#             */
/*   Updated: 2023/05/25 16:36:24 by psydenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// INCLUDE 42 HEADER

#include "../inc/cub3d.h"

int	validate_main(t_map *map)
{
	biggest_width(map);
	if(wall_check(map))
			return (1);
	else
	{
		ft_printf("Not a valid map\n");
		return (0);
	}
}

void	biggest_width(t_map *map)
{
	int x;

	x = 0;
	map->window_width = ft_strlen(map->world_map[x]);
	while(map->world_map[x])
	{
		if ((int)ft_strlen(map->world_map[x]) > map->window_width)
			   map->window_width = (int)ft_strlen(map->world_map[x]);	
		x++;
	}
}

int	wall_check(t_map *map)
{
	int	y;

	y = 0;
	while (map->world_map[0][y])
	{
		if (map->world_map[0][y] != '1')
			return (0);
		y++;
	}
	y = 0;
	while (map->world_map[map->window_height - 1][y])
	{
		if (map->world_map[map->window_height - 1][y] != '1')
			return (0);
		y++;
	} 
	if (wall_check2(map) == 1)
		return (1);
	else
		return (0);
}

int	wall_check2(t_map *map)
{	
	int	y;

	y = 0;
	while (map->world_map[y])
	{
		if (map->world_map[y][0] != '1')
			return (0);
		y++;
	}
	y = 0;
	while (map->world_map[y])
	{
		if (map->world_map[y][ft_strlen(map->world_map[y]) - 1] != '1')
			return (0);
		y++;
	}
	return (1);
}

