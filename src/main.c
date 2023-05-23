/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:24:48 by almelo            #+#    #+#             */
/*   Updated: 2023/05/22 22:59:00 by psydenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/cub3d.h"
#include "../libft/libft.h"
#include <fcntl.h>

int	verification_main(char **argv)
{
	int fd;

	fd = 0;
	if (validate_cub(argv[1]) == 0)
	{
		ft_printf("Not a .cub :/");
		return (0);
	}
//	fd = open(argv[1], O_RDONLY);
//	ft_create_map(fd);	
	return (1);
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

int	main( int argc, char **argv)
{
	t_data	data;

	if (!verification_main(argv))
			return (0);
	(void) argc;
	(void) argv;
	data.pos_x = 22, data.pos_y = 11.5; //x and y start position
	data.dir_x = -1, data.dir_y = 0; //initial direction vector
	data.plane_x = 0, data.plane_y = 0.66; //the 2d raycaster version of camera plane
	
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
	set_hooks(&data);
	mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_loop(data.mlx);
	return (0);
}
