// INCLUDE 42 HEADER
#include "../inc/cub3d.h" 

void	free_main(t_data *data)
{
	free(data->map.path_NO);
	free(data->map.path_SO);
	free(data->map.path_WE);
	free(data->map.path_EA);
	free(data->map.floor);
	free(data->map.ciel);
	free_matrix(&data->map);
}

void	free_matrix(t_map *map)
{
	while(map->world_map[map->map_start])
	{
		free(map->world_map[map->map_start]);
		map->map_start++;
	}
}


