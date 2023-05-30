/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 04:36:07 by almelo            #+#    #+#             */
/*   Updated: 2023/05/30 00:00:12 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

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
	t_img	tex_NO;
	t_img	tex_SO;
	t_img	tex_WE;
	t_img	tex_EA;
	int		tex_width;
	int		tex_height;
}			t_data;

typedef struct s_line
{
	int	x;
	int	height;
	int	y_start;
	int	y_end;
	int	color;
}		t_line;

typedef struct s_plane_vector
{
	double	x;
	double	y;
}			t_plane_vector;

typedef struct s_dir_vector
{
	double	x;
	double	y;
}			t_dir_vector;
