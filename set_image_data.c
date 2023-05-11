/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_new_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:28:14 by almelo            #+#    #+#             */
/*   Updated: 2023/05/11 17:47:44 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_image_data(t_img *img)
{
	img->addr = mlx_get_data_addr
		(
			img->img,
			&img->bits_per_pixel,
			&img->line_length,
			&img->endian
			);
	return ;
}
