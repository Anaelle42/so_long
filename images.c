/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:35:42 by ahenault          #+#    #+#             */
/*   Updated: 2024/04/09 19:22:09 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	xpm(t_data *struc)
{
	struc->mur = mlx_xpm_file_to_image(struc->mlx, "./xpm/stop.xpm",
			&struc->img_width, &struc->img_height);
	struc->sol = mlx_xpm_file_to_image(struc->mlx, "./xpm/grass.xpm",
			&struc->img_width, &struc->img_height);
	struc->perso = mlx_xpm_file_to_image(struc->mlx, "./xpm/mael.xpm",
			&struc->img_width, &struc->img_height);
	struc->coin = mlx_xpm_file_to_image(struc->mlx, "./xpm/banana.xpm",
			&struc->img_width, &struc->img_height);
	struc->porte = mlx_xpm_file_to_image(struc->mlx, "./xpm/porte.xpm",
			&struc->img_width, &struc->img_height);
}

void	affiche_toi(t_data *struc, void *img, int x, int y)
{
	mlx_put_image_to_window(struc->mlx, struc->win, img, x * struc->img_width, y
		* struc->img_height);
}

void	images(t_data *struc, char **map)
{
	int x;
	int y;

	x = 0;
	y = 0;
	//xpm(struc);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				affiche_toi(struc, struc->mur, x, y);
			else if (map[y][x] == 'P')
				affiche_toi(struc, struc->perso, x, y);
			else if (map[y][x] == 'E')
				affiche_toi(struc, struc->porte, x, y);
			else if (map[y][x] == 'C')
				affiche_toi(struc, struc->coin, x, y);
			else if (map[y][x] != '\n')
				affiche_toi(struc, struc->sol, x, y);
			x++;
		}
		y++;
	}
}