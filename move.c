/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:38:24 by ahenault          #+#    #+#             */
/*   Updated: 2024/04/10 19:37:22 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* D = 100.	A = 97. W = 119. S = 115*/
void	bouge(t_data *str, int h, int l)
{
	if ((str->data_map.map[str->y + h][str->x + l] != '1'
			&& str->data_map.map[str->y + h][str->x + l] != 'E')
		|| (str->data_map.map[str->y + h][str->x + l] == 'E' && str->c == 0))
	{
		mlx_put_image_to_window(str->mlx, str->win, str->sol, str->x
			* str->img_width, str->y * str->img_height);
		str->x += l;
		str->y += h;
		mlx_put_image_to_window(str->mlx, str->win, str->perso, str->x
			* str->img_width, str->y * str->img_height);
		str->compte_mvts++;
		printf("Compte : %i\n", str->compte_mvts);
	}
}

void	wich_key(int key, t_data *str)
{
	if (key == 100)
		bouge(str, 0, 1);
	if (key == 97)
		bouge(str, 0, -1);
	if (key == 115)
		bouge(str, 1, 0);
	if (key == 119)
		bouge(str, -1, 0);
}

int	fonction(int key, t_data *str)
{
	// images(str, str->data_map.map);
	if (key == 65307)
		finito(str);
	wich_key(key, str);
	if (str->data_map.map[str->y][str->x] == 'C')
	{
		str->data_map.map[str->y][str->x] = '0';
		str->c--;
		str->score++;
		printf("	Score : %i\n", str->score);
	}
	if (str->data_map.map[str->y][str->x] == 'E')
	{
		printf("	Fini !! \n");
		finito(str);
	}
	return (0);
}
