/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verification.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psydenst <psydenst@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 21:33:00 by psydenst          #+#    #+#             */
/*   Updated: 2023/06/02 22:52:39 by psydenst         ###   ########.fr       */
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

/*
int	wall_spaces(t_map *map)
{
	char	**map_copy;
	int		i;
	char	**joker;
	int 	z;

	z = 0;
	i = 0;
	map_copy = malloc(sizeof(char **));
	while (map->world_map[i])
	{
		joker = ft_strdup(map->world_map[i]);
		z = ft_strlen(joker);
		while (z < map->window_width)
		{
			map_copy[i] = ft_strjoin(joker, "k");
			z++;
		}
		i++;
		free(joker);
	}
	i = 0;
	while (map_copy[i])
	{
		printf("%s\n", map_copy[i]);
		i++;
	}
	if (check_above(map_copy, map->window_height) == 0)
		map->valid = -1;
	i = 0;
	while (i < map->window_height)
	{
		free(map_copy[i]);
		i++;
	}
	if (map->valid == -1)
		return (0);
	return (1);
} */

int	wall_spaces(t_map *map)
{
	char	**map_copy;
	int		i;
	int		z;
	int		j;

	i = 0;
	map_copy = malloc(sizeof(char **));
	while (i < map->window_height)
	{
		j = 0;
		z = map->window_width - ft_strlen(map->world_map[i]);
		map_copy[i] = malloc(sizeof(char) * map->window_width);
		while (j < map->window_width)
		{
			if (j < z)
				map_copy[i][j] = map->world_map[i][j];
			if (j >= z)
				map_copy[i][j] = 'k';
			j++;
		}
		i++;
	}
	int k = 0;
	while(map_copy[k])
	{
		printf("%s\n", map_copy[k]);
		k++;
	}
	return (1);
}


int	check_above(char **str, int height)
{
	int	i;
	int	j;

	i = 1;
	while (i < height)
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '0')
			{
				if (str[i - 1][j] == 'k' || str[i][j + 1] == 'k' ||
				str[i][j - 1] == 'k')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
