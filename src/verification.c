/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verification.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psydenst <psydenst@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 21:33:00 by psydenst          #+#    #+#             */
/*   Updated: 2023/06/09 20:50:58 by psydenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_is_cub(char *haystack)
{
	if (ft_strnstr(haystack, ".cub", 4))
	{
		free(haystack);
		return (1);
	}
	else
	{
		free(haystack);
		return (0);
	}
}

int	validate_cub(char *map_name)
{
	int		a;
	int		b;
	int		x;
	char	*haystack;

	a = 4;
	x = 0;
	if (ft_strlen(map_name) < 5)
		return (0);
	b = ft_strlen(map_name) - 4;
	haystack = malloc(5 * sizeof(char));
	if (!haystack)
		return (0);
	while (a > 0)
	{
		haystack[x] = map_name[b];
		x++;
		b++;
		a--;
	}
	if (ft_is_cub(haystack) == 1)
		return (1);
	else
		return (0);
}

int	verification_main(char **argv, int argc, t_data *data)
{
	if (argc != 2)
	{
		ft_printf("Wrong input :/\nUsage: ./cub3d path_to_.cub\n");
		return (0);
	}
	if (validate_cub(argv[1]) == 0)
	{
		ft_printf("Not a .cub :/\n");
		return (0);
	}
	data->map.fd = open(argv[1], O_RDONLY);
	if (data->map.fd > 0)
		create_map(data);
	else
	{
		ft_printf("Map and textures instruction were not found\n");
		return (0);
	}
	if (validate_main(&data->map) == 0)
		return (0);
	return (1);
}

int	wall_spaces(t_map *map)
{
	int a;

	map->i = 0;
	map->length = 0;
	map->map_copy = malloc(sizeof(char *) * map->window_height);
	map->i = -1;
	a = 0;
	while (map->i++ < map->window_height - map->map_start - 1)
		map->map_copy[map->i] = malloc(sizeof(char *) * (map->window_width + 1));
	map->i = map->map_start;
	while (map->i < map->window_height)
	{
		map->j = 0;
		while (map->j < map->window_width)
		{
			if (map->world_map[map->i][map->j] != '\0')
				map->map_copy[a][map->j] = map->world_map[map->i][map->j];
			else
				map->map_copy[a][map->j] = 'k';
			map->j++;
		}
		map->map_copy[a][map->j] = '\0';
		map->i++;
		a++;
	}
	int f = 0;
	while (map->map_copy[f])
	{
		printf("%s\n", map->map_copy[f]);
		f++;
	}
	return (1);
}


int	check_above(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->window_height - map->map_start - 1)
	{
		j = 0;
		while (map->map_copy[i][j])
		{
			if (map->map_copy[i][j] == '0')
			{
				if (map->map_copy[i - 1][j] == 'k' ||map->map_copy [i][j + 1] == 'k' ||
				map->map_copy[i][j - 1] == 'k')
					return (0);
			}
			j++;
		}
		i++;
	}
	i = -1;
	while (++i < map->window_height - 1)
		free(map->map_copy[i]);
	free(map->map_copy);
	return (1);
}
