/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psydenst <psydenst@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:03:20 by psydenst          #+#    #+#             */
/*   Updated: 2023/06/01 18:05:42 by psydenst         ###   ########.fr       */
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
	printf("%i\n", nsow10(map, i));
	if (nsow10(map, i) == 0)
		return (0);
	if(wall_spaces(map) == 0)
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

int nsow10(t_map *map, int x)
{
    int i;

    i = 0;
//    if (map->world_map[x] == NULL)
//        return (1);
    while (x < map->window_height)
	{
		while (map->world_map[x][i])
		{
        	if (map->world_map[x][i] != '1' && map->world_map[x][i] != '0' &&
				map->world_map[x][i] != 'N' && map->world_map[x][i] != 'O' 
				&& map->world_map[x][i] != 'W' && map->world_map[x][i]!='S')
            	return (0);
        	if (map->world_map[x][i] == 'N' || map->world_map[x][i] == 'S' ||
            	    map->world_map[x][i] == 'O' || map->world_map[x][i] == 'W')
        	{
            	map->pos_x = x;
            	map->pos_y = i;
            	map->direction = map->world_map[x][i];
            	map->sign++;
        	}
        	i++;
    	}
    	if (map->sign > 1)
			return (0);
		x++;
	}
	return (1);
}
