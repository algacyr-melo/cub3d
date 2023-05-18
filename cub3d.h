/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:21:09 by almelo            #+#    #+#             */
/*   Updated: 2023/05/18 15:40:48 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define SCREEN_WIDTH	640
# define SCREEN_HEIGHT	480
# define TITLE			"Hello, Raycasting"

# define ROT_SPEED		0.05
# define MOVE_SPEED		0.1

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>

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
	void	*mlx;
	void	*win;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}			t_data;

void	set_image_data(t_img *img);

int		render_next_frame(t_data *data);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_vertical_line(t_img *img, t_line *line);

void	set_hooks(t_data *data);
#endif
