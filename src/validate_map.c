/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psydenst <psydenst@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:03:20 by psydenst          #+#    #+#             */
/*   Updated: 2023/05/25 22:22:59 by psydenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// INCLUDE 42 HEADER

#include "../inc/cub3d.h"

int	validate_main(t_map *map)
{
	if (textures_main(map) == 0)
			return (0);
	biggest_width(map);
/*
	if(wall_check(map))
			return (1);
	else
	{
		ft_printf("Not a valid map\n");
		return (0);
	} */
	return (1);
}

/*
int	is_valid(t_map *map)
{
	int x;
	int y;

	x = map->map_start;
	y = 0;
	while (map->world_map[x][y])
	{	
		if (map->world_map[x][y] != 1)
			return (0);
		y++;
	}
	x++;
	y = 0;
	while(map->world_map[x])
	{
		while (map->world_map[x][y])
		{		
				if (map->world_map[x][y] == '0')
					if (map->world_map[x - 1][y] != '1')
						return (0);
				y++;
		}
		x++;
	}
} */

void	biggest_width(t_map *map)
{
	int x;
	int y;
	x = 0;
	while (map->world_map[x] == NULL)
			x++;
	map->map_start = x;
	y = x + 1;
	while (map->world_map[y])
			y++;
	map->window_height = y - x + 1;
	printf("window->height: %i\n", map->window_height);
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

