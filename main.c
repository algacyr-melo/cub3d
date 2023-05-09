/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:48:30 by almelo            #+#    #+#             */
/*   Updated: 2023/05/08 21:35:26 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_square(t_data *data, int x, int y, int size, int color)
{
	int	x_offset;
	int	y_offset;

	x_offset = 0;
	while (x_offset < size)
	{
		y_offset = 0;
		while (y_offset < size)
		{
			my_mlx_pixel_put(data, x + x_offset, y + y_offset, color);
			y_offset++;
		}
		x_offset++;
	}
	return ;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 600, "Hello, MLX!");
	img.img = mlx_new_image(mlx, 800, 600);
	img.addr = mlx_get_data_addr
	(
		img.img,
		&img.bits_per_pixel,
		&img.line_length,
		&img.endian
	);
	draw_square(&img, 42, 42, 42, 0x0FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
