/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psydenst <psydenst@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 22:00:29 by psydenst          #+#    #+#             */
/*   Updated: 2023/06/02 22:46:38 by psydenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	wall_spaces(t_map *map)
{
	char	**map_copy;
	int		i;
	int		z;
	int		j;

	i = 0;
	map_copy = malloc(sizeof(char **));
	while (map->world_map[i])
	{
		j = 0;
		z = map->window_width - ft_strlen(map->world_map[i]);
		map_copy[i] = malloc(sizeof(char) * map->window_width);
		while (j < map->window_width)
		{
			if (j < z)
				map_copy[i] = map->world_map[i][j];
			if (j >= z)
				map_copy[i] = 'k';
			j++;
		}
		i++;
	}

	return (1);
}
