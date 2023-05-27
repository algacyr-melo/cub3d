/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verification.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psydenst <psydenst@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 21:33:00 by psydenst          #+#    #+#             */
/*   Updated: 2023/05/25 21:52:04 by psydenst         ###   ########.fr       */
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
	if ((data->map.fd = open(argv[1], O_RDONLY)) > 0)
		create_map(data);
	else
	{
		ft_printf("Map and textures instruction were not found\n");
		return (0);
	}
	if(validate_main(&data->map) == 0)
		return (0);
	printf("\n\n");
	printf("Valor de map->path_NO: %s\n", data->map.path_NO);
	printf("Valor de map->path_SO: %s\n", data->map.path_SO);
	printf("Valor de map->path_WE: %s\n", data->map.path_WE);
	printf("Valor de map->path_EA: %s\n", data->map.path_EA);
	
	
	
	
	return (1);
}


