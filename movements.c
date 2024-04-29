/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:38:24 by ahenault          #+#    #+#             */
/*   Updated: 2024/04/12 20:07:17 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player(t_data *data, int h, int w)
{
	if ((data->map.map[data->player.y + h][data->player.x + w] != '1'
		&& data->map.map[data->player.y + h][data->player.x + w] != 'E')
		|| (data->map.map[data->player.y + h][data->player.x + w] == 'E'
		&& data->player.c == 0))
	{
		mlx_put_image_to_window(data->mlx, data->win, data->img.floor,
			data->player.x * data->img.img_width, data->player.y
			* data->img.img_height);
		data->player.x += w;
		data->player.y += h;
		mlx_put_image_to_window(data->mlx, data->win, data->img.player,
			data->player.x * data->img.img_width, data->player.y
			* data->img.img_height);
		data->player.movements++;
		ft_printf("Movements : %i\n", data->player.movements);
	}
}

void	which_key(int key, t_data *data)
{
	if (key == 100)
		move_player(data, 0, 1);
	if (key == 97)
		move_player(data, 0, -1);
	if (key == 115)
		move_player(data, 1, 0);
	if (key == 119)
		move_player(data, -1, 0);
}

int	key_hook(int key, t_data *data)
{
	if (key == 65307)
		on_destroy(data);
	which_key(key, data);
	if (data->map.map[data->player.y][data->player.x] == 'C')
	{
		data->map.map[data->player.y][data->player.x] = '0';
		data->player.c--;
		data->player.score++;
		ft_printf("	Score : %i\n", data->player.score);
	}
	if (data->map.map[data->player.y][data->player.x] == 'E')
	{
		ft_printf("	To be continued... \n");
		on_destroy(data);
	}
	return (0);
}

int	on_destroy(t_data *data)
{
	if (data->img.wall)
		mlx_destroy_image(data->mlx, data->img.wall);
	if (data->img.floor)
		mlx_destroy_image(data->mlx, data->img.floor);
	if (data->img.exit)
		mlx_destroy_image(data->mlx, data->img.exit);
	if (data->img.collectible)
		mlx_destroy_image(data->mlx, data->img.collectible);
	if (data->img.player)
		mlx_destroy_image(data->mlx, data->img.player);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free_tab(data->map.map);
	free(data->mlx);
	exit(1);
	return (0);
}
