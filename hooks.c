/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:38:11 by almelo            #+#    #+#             */
/*   Updated: 2023/05/16 17:17:58 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

enum
{
	ESC = 65307,
	W = 119,
	A = 97,
	S = 115,
	D = 100
};

enum
{
	ON_KEYDOWN = 2,
	ON_DESTROY = 17
};

void	handle_exit(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}

int	handle_keydown(int keycode, t_mlx *mlx)
{
	printf("%d\n", keycode);
	if (keycode == ESC)
		handle_exit(mlx);
	return (0);
}

int	handle_destroy(t_mlx *mlx)
{
	handle_exit(mlx);
	return (0);
}

void	set_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, ON_KEYDOWN, 1L << 0, handle_keydown, mlx);
	mlx_hook(mlx->win, ON_DESTROY, 1L << 2, handle_destroy, mlx);
}
