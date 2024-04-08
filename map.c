/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:07:12 by ahenault          #+#    #+#             */
/*   Updated: 2024/04/08 21:15:07 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// TODO: free, fermer la map, fin

t_map	load_map(char *file)
{
	t_list	*list;
	t_map	map;
	int		fd;
	int		i;
	char	*line;

	line = NULL;
	list = NULL;
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error(ERROR2);
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_lstadd_back(&list, ft_lstnew((void *)line));
		line = get_next_line(fd);
		i++;
	}
	map.map = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (list)
	{
		map.map[i] = list->content;
		list = list->next;
		i++;
	}
	map.map[i] = NULL;
	return (map);
}

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

void	images(t_data *struc, char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	xpm(struc);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				mlx_put_image_to_window(struc->mlx, struc->win, struc->mur, x
					* struc->img_width, y * struc->img_height);
			}
			else if (map[y][x] == 'P')
			{
				mlx_put_image_to_window(struc->mlx, struc->win, struc->perso, x
					* struc->img_width, y * struc->img_height);
			}
			else if (map[y][x] == 'E')
			{
				mlx_put_image_to_window(struc->mlx, struc->win, struc->porte, x
					* struc->img_width, y * struc->img_height);
			}
			else if (map[y][x] == 'C')
			{
				mlx_put_image_to_window(struc->mlx, struc->win, struc->coin, x
					* struc->img_width, y * struc->img_height);
			}
			else if (map[y][x] != '\n')
			// if (map[y][x] == '0')
			{
				mlx_put_image_to_window(struc->mlx, struc->win, struc->sol, x
					* struc->img_width, y * struc->img_width);
			}
			x++;
		}
		y++;
	}
}

/* D = 100.	A = 97. W = 119. S = 115*/

int	fonction(int key, t_data *str)
{
	if (key == 65307)
	{
		mlx_destroy_window(str->mlx, str->win);
		mlx_destroy_display(str->mlx);
	}
	// images(str, str->data_map.map);
	if (str->data_map.map[str->y][str->x] == 'C')
	{
		str->data_map.map[str->y][str->x] = '0';
		str->c--;
		printf("coin restant : %i\n", str->c);
	}
	if (key == 100 && str->data_map.map[str->y][str->x + 1] != '1'
		&& str->data_map.map[str->y][str->x + 1] != 'E')
	{
		mlx_put_image_to_window(str->mlx, str->win, str->sol, str->x
			* str->img_width, str->y * str->img_height);
		mlx_put_image_to_window(str->mlx, str->win, str->perso, str->x
			* str->img_width + str->img_width, str->y * str->img_height);
		printf("droite = %i \n", key);
		str->x += 1;
	}
	if (key == 97 && str->data_map.map[str->y][str->x - 1] != '1'
		&& str->data_map.map[str->y][str->x - 1] != 'E')
	{
		mlx_put_image_to_window(str->mlx, str->win, str->sol, str->x
			* str->img_width, str->y * str->img_height);
		mlx_put_image_to_window(str->mlx, str->win, str->perso, str->x
			* str->img_width - str->img_width, str->y * str->img_height);
		printf("gauche = %i \n", key);
		str->x -= 1;
	}
	if (key == 115 && str->data_map.map[str->y + 1][str->x] != '1'
		&& str->data_map.map[str->y + 1][str->x] != 'E')
	{
		mlx_put_image_to_window(str->mlx, str->win, str->sol, str->x
			* str->img_width, str->y * str->img_height);
		mlx_put_image_to_window(str->mlx, str->win, str->perso, str->x
			* str->img_width, str->y * str->img_height + str->img_height);
		printf("bas = %i \n", key);
		str->y += 1;
	}
	if (key == 119 && str->data_map.map[str->y - 1][str->x] != '1'
		&& str->data_map.map[str->y - 1][str->x] != 'E')
	{
		mlx_put_image_to_window(str->mlx, str->win, str->sol, str->x
			* str->img_width, str->y * str->img_height);
		mlx_put_image_to_window(str->mlx, str->win, str->perso, str->x
			* str->img_width, str->y * str->img_height - str->img_height);
		printf("haut = %i \n", key);
		str->y -= 1;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		i;
	t_data	str;

	i = 0;
	if (argc != 2 || check_extension(argv[1]) == 0)
		ft_error(ERROR1);
	str.data_map = load_map(argv[1]);
	parsing(&str);
	while (str.data_map.map[i])
	{
		printf("%s", str.data_map.map[i]);
		i++;
	}
	str.mlx = mlx_init();
	str.win = mlx_new_window(str.mlx, 80 * str.nb_x, 80 * str.nb_y, "Hello");
	images(&str, str.data_map.map);
	mlx_hook(str.win, KeyPress, KeyPressMask, fonction, &str);
	mlx_loop(str.mlx);
}
