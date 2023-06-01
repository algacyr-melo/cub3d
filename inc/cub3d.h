/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:21:09 by almelo            #+#    #+#             */
/*   Updated: 2023/06/01 02:42:12 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define TITLE			"Hello, Raycasting"
# define SCREEN_WIDTH	800
# define SCREEN_HEIGHT	600
# define ROT_SPEED		0.1
# define MOVE_SPEED		0.25

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>

# include "types.h"
# include "raycaster.h"
# include "frame.h"

# include "../libft/header/libft.h" 
# include "../libft/header/ft_printf.h"
# include "../libft/header/get_next_line.h"
# include <fcntl.h>

// OS detection
#ifdef __linux__
# include "../inc/hooks_linux.h"
#elif defined(__APPLE__)
# include "../inc/hooks_mac.h"
#endif

// VERIFICATION.C
int	validate_cub(char *map_name);
int	ft_is_cub(char *haystack);
int	ft_is_cub(char *haystack);
int	verification_main(char **argv, int argc, t_data *data);

// FREE_MAIN.C
void	free_main(t_data *data);
void	free_matrix(t_map *map);

// 	TEXTURES_PATH
int	textures_main(t_map *map);
int	get_NO(t_map *map, int i);
int	get_SO(t_map *map, int i);
int	get_WE(t_map *map, int i);
int	get_EA(t_map *map, int i);
int	not_map(t_map *map, int i);
int	floor_ciel(t_map *map, int i);

// CREATE_MAP.C
void	create_map(t_data *data);
void	to_matrix(t_data *data, char *joker);
char 	*remove_sp(char *str);

// VALIDATE_MAP.C
int		validate_main(t_map *map);
int		wall_check(t_map *map);
int		wall_check2(t_map *map);
void	biggest_width(t_map *map);
int 	is_one(t_map *map, int i);
int		is_valid(t_map *map);

// Set struct with mlx image data
void	set_image_data(t_img *img);

void	set_hooks(t_data *data);
void	load_textures(t_data *data);
void	load_colors(t_data *data);
void	set_player_position(t_data *data);
void	set_player_direction(t_data *data);
int		render_next_frame(t_data *data);
void	raycaster_loop(t_raycaster *rc, t_data *data, t_frame *frame);
void	set_texture_x(t_raycaster *rc, t_data *data);
void	set_wall_pixel_x(t_raycaster *rc, t_data *data);
void	buffer_ceil_v_line(t_raycaster *rc, t_data *data, t_frame *frame);
void	buffer_floor_v_line(t_raycaster *rc, t_data *data, t_frame *frame);
void	buffer_wall_v_line(t_raycaster *rc, t_data *data, t_frame *frame);
void	draw_next_frame(t_img *img, uint32_t (*buffer)[SCREEN_WIDTH]);
void	clear_frame_buffer(t_frame *frame);

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
#endif
