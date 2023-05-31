/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 04:36:07 by almelo            #+#    #+#             */
/*   Updated: 2023/05/31 02:25:10 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "img.h"

typedef struct s_data
{
	t_map		map;
	void		*mlx;
	void		*win;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	t_img		tex_NO;
	t_img		tex_SO;
	t_img		tex_WE;
	t_img		tex_EA;
	int			tex_width;
	int			tex_height;
	char		spawn_orientation;
	uint32_t	color_ceil;	
	uint32_t	color_floor;
}			t_data;

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
#endif
