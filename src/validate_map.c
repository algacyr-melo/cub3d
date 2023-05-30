/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psydenst <psydenst@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:03:20 by psydenst          #+#    #+#             */
/*   Updated: 2023/05/30 16:37:19 by psydenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// INCLUDE 42 HEADER

#include "../inc/cub3d.h"

int	validate_main(t_map *map)
{
	if (textures_main(map) == 0)
	{
		printf("Invalid textures\n");
		return (0);
	}
	biggest_width(map);
	if (is_valid(map) == 0)
	{
		printf("Invalid map\n");
		return (0);
	}
	return (1);
}

int	is_valid(t_map *map)
{
	int height;
	int i;

	i = 1;
	height = 0;
	while (map->world_map[height])
		height++;
	if (is_one(map, 0) == 0 || is_one(map, height - 1) == 0)
		return (0);

	return (1);
}

int is_one(t_map *map, int i)
{
	int j;

	j = 0;
	while (map->world_map[i][j])
	{
		if (map->world_map[i][j] != '1')
			return (0);
		j++;
	}
	return (1);
}

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
	map->window_height = y - x;
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

