/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:35:42 by ahenault          #+#    #+#             */
/*   Updated: 2024/04/15 14:15:54 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_xpm_images(t_data *data)
{
	data->img.wall = mlx_xpm_file_to_image(data->mlx, "./xpm/rock.xpm",
			&data->img.img_width, &data->img.img_height);
	data->img.floor = mlx_xpm_file_to_image(data->mlx, "./xpm/grass.xpm",
			&data->img.img_width, &data->img.img_height);
	data->img.player = mlx_xpm_file_to_image(data->mlx, "./xpm/player.xpm",
			&data->img.img_width, &data->img.img_height);
	data->img.collectible = mlx_xpm_file_to_image(data->mlx,
			"./xpm/banana.xpm", &data->img.img_width, &data->img.img_height);
	data->img.exit = mlx_xpm_file_to_image(data->mlx, "./xpm/exit.xpm",
			&data->img.img_width, &data->img.img_height);
	if (!data->img.exit || !data->img.floor || !data->img.collectible
		|| !data->img.wall || !data->img.player)
	{
		ft_printf("Error\nWhen trying to open texture files\n");
		on_destroy(data);
	}
}

void	put_image(t_data *data, void *img, int x, int y)
{
	mlx_put_image_to_window(data->mlx, data->win, img, x * data->img.img_width,
		y * data->img.img_height);
}

void	display_images(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (data->map.map[y])
	{
		x = 0;
		while (data->map.map[y][x])
		{
			if (data->map.map[y][x] == '1')
				put_image(data, data->img.wall, x, y);
			else if (data->map.map[y][x] == 'P')
				put_image(data, data->img.player, x, y);
			else if (data->map.map[y][x] == 'E')
				put_image(data, data->img.exit, x, y);
			else if (data->map.map[y][x] == 'C')
				put_image(data, data->img.collectible, x, y);
			else if (data->map.map[y][x] != '\n')
				put_image(data, data->img.floor, x, y);
			x++;
		}
		y++;
	}
}
