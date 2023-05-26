/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:21:09 by almelo            #+#    #+#             */
/*   Updated: 2023/05/25 18:56:50 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//# define SCREEN_WIDTH	1200
//# define SCREEN_HEIGHT	1000

# define SCREEN_WIDTH	800
# define SCREEN_HEIGHT	600

# define TITLE			"Hello, Raycasting"

# define ROT_SPEED		0.1
# define MOVE_SPEED		0.3

//only works with the tutorial map
# define MAP_WIDTH		24
# define MAP_HEIGHT		24

extern int world_map[MAP_WIDTH][MAP_HEIGHT];

//# include "mlx_linux/mlx.h"
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include "maps.h"
//# include "../libft/libft.h" 
# include "../libft/header/libft.h" 
# include "../libft/header/ft_printf.h"
# include "../libft/header/get_next_line.h"
# include <fcntl.h>

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_line
{
	int	x;
	int	height;
	int	y_start;
	int	y_end;
	int	color;
}		t_line;

typedef struct s_data
{
	t_map	map;
	void	*mlx;
	void	*win;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}			t_data;

// VERIFICATION.C
int	validate_cub(char *map_name);
int	ft_is_cub(char *haystack);
int	ft_is_cub(char *haystack);
int	verification_main(char **argv, int argc, t_data *data);


// CREATE_MAP.C
void	create_map(t_data *data);
void	to_matrix(t_data *data, char *joker);
char 	*remove_sp(char *str);

// VALIDATE_MAP.C
int		validate_main(t_map *map);
int		wall_check(t_map *map);
int		wall_check2(t_map *map);
void	biggest_width(t_map *map);

//set struct with mlx image data
void	set_image_data(t_img *img);

int		render_next_frame(t_data *data);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_next_frame(t_img *img, uint32_t (*buffer)[SCREEN_WIDTH]);

void	set_hooks(t_data *data);
#endif
