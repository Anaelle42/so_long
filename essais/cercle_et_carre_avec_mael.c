/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cercle_et_carre_avec_mael.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:19:12 by ahenault          #+#    #+#             */
/*   Updated: 2024/03/28 19:20:33 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct s_data
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
	*(unsigned int *)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*win;
	t_data	img;
	int		x;
	int		y;
	int		color;
	int		rayon;
	int		d;
	int		i;

	color = 0xFF0000;
	x = 400;
	y = 400;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1000, 600, "Hello");
	img.img = mlx_new_image(mlx, 1000, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	//
	i = 0;
	while (i <= 100)
	{
		color += 0xFFFF00 * 0.000035;
		my_mlx_pixel_put(&img, x + i, y + 100, color);
		my_mlx_pixel_put(&img, x + i, y, color);
		my_mlx_pixel_put(&img, x, y + i, color);
		my_mlx_pixel_put(&img, x + 100, y + i, color);
		i++;
	}
	//
	rayon = 100;
	x = 0, y = rayon;
	d = 3 - 2 * rayon;
	while (y >= x)
	{
		color += color * 0.00006;
		my_mlx_pixel_put(&img, 100 + x, 100 + y, color);
		my_mlx_pixel_put(&img, 100 - x, 100 + y, color);
		my_mlx_pixel_put(&img, 100 + x, 100 - y, color);
		my_mlx_pixel_put(&img, 100 - x, 100 - y, color);
		my_mlx_pixel_put(&img, 100 + y, 100 + x, color);
		my_mlx_pixel_put(&img, 100 - y, 100 + x, color);
		my_mlx_pixel_put(&img, 100 + y, 100 - x, color);
		my_mlx_pixel_put(&img, 100 - y, 100 - x, color);
		if (d <= 0)
		{
			d = d + 4 * x + 6;
		}
		else
		{
			d = d + 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
	//
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
}
