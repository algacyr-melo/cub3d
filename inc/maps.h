/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psydenst <psydenst@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:44:08 by psydenst          #+#    #+#             */
/*   Updated: 2023/05/27 01:50:57 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPS_H
#define MAPS_H

typedef struct s_map
{
	int		fd;
	int		window_height;
	int		window_width;
	int		map_start;
	char	*path_NO;
	char	*path_SO;
	char	*path_WE;
	char	*path_EA;
	char	**world_map;
	char	*floor;
	char	*ciel;
    int     pos_x;
    int     pos_y;
    char    direction;
    int     sign;
	int		valid;
} t_map;

#endif

