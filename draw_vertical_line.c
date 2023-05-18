/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vertical_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:56:55 by almelo            #+#    #+#             */
/*   Updated: 2023/05/18 15:13:44 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vertical_line(t_img *img, t_line *line)
{
	int	offset;

	offset = 0;
	while (offset < (line->y_end - line->y_start))
	{
		my_mlx_pixel_put(img, line->x, line->y_start + offset, line->color);
		offset++;
	}
	return ;
}
