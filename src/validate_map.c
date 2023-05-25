// INCLUDE 42 HEADER

#include "../inc/cub3d.h"

int	validate_main(t_map *map)
{
	int i = 0;
	while (map->world_map[i])
			i++;
	map->window_heigth = i - 1;
	if(wall_check(map))
			return (1);
	return (0);
}

void	biggest_width(t_map *map)
{
	int x;

	x = 0;
	map->window_width = ft_strlen(map->world_map[x]);
	while(map->world_map[x])
	{
		if (ft_strlen(map->world_map[x]) > map->window_width)
			   window_width = ft_strlen(map->world_map[x]);	
		x++;
	}
}

int	wall_check(t_map *map)
{
	int	y;

	y = 0;
	while (map->map[0][y])
	{
		if (map->map[0][y] != '1')
			return (0);
		y++;
	}
	y = 0;
	while (map->map[map->window_height][y])
	{
		if (map->map[map->window_height][y] != '1')
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
	while (map->map[y])
	{
		if (map->map[y][0] != '1')
			return (0);
		y++;
	}
	y = 0;
	while (map->map[y])
	{
		if (map->map[y][ft_strlen(map->map[y]) - 1] != '1')
			return (0);
		y++;
	}
	return (1);
}

