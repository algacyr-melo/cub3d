/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psydenst <psydenst@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 22:23:28 by psydenst          #+#    #+#             */
/*   Updated: 2023/05/25 23:14:00 by psydenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	textures_main(t_map *map)
{
	int i;
	int j;

	j = 2;
	i = 0;
	if (ft_strncmp(map->world_map[i], "NO", 2) == 0)
	{
		if(get_NO(map, i) == 0)
			return (printf("Texture not found\n");
	}
	else if (ft_strncmp(map->world_map[i], "SO", 2) == 0)
	{
		if(get_NO(map, i) == 0)
			return (printf("Texture not found\n");
	}
	else if (ft_strncmp(map->world_map[i], "WE", 2) == 0)
	{
		if(get_NO(map, i) == 0)
			return (printf("Texture not found\n");
	}
	else if (ft_strncmp(map->world_map[i], "EA", 2) == 0)
	{
		if(get_NO(map, i) == 0)
			return (printf("Texture not found\n");
	}
	return (1);
}

int	get_NO(t_map *map, int i)
{
	int fd;
	map->world_map[i] += 2;
	if ((fd = open(map->world_map[i], O_RDONLY) > 0))
	{	
		map->path_NO = ft_strdup(map->world_map[i]);
		return (1);
	}
	return (0);
}

int	get_SO(t_map *map, int i)
{
	int fd;
	map->world_map[i] += 2;
	if ((fd = open(map->world_map[i], O_RDONLY) > 0))
	{	
		map->path_NO = ft_strdup(map->world_map[i]);
		return (1);
	}
	return (0);
}

int	textures
	if (ft_strncmp(map->world_map[i], "WE", 2) == 0)
	{
		map->world_map[i] += 2;
	//	ft_printf("my string is: %s\n", map->world_map[i]);
		if (open(map->world_map[i], O_RDONLY) > 0)
			map->path_NO = ft_strdup(map->world_map[i]);	
		else
			return (ft_printf("Texture not found\n"));
	}
	ft_printf("Chegay\n");
	return (1);
}

/*
int	textures_path(t_map *map)
{
	(void)map;
	ft_printf("%i\n", ft_strncmp(map->world_map[i], "NO", 2));


} */
