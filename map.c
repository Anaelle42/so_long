/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:07:12 by ahenault          #+#    #+#             */
/*   Updated: 2024/04/05 18:12:15 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// TODO: map +6 lignes

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
	map.map = malloc(sizeof(char *) * i);
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

void	images(t_data *struc, char **map)
{
	int	x;
	int	y;
	int	img_height;
	int	img_width;

	x = 0;
	y = 0;
	struc->mur = mlx_xpm_file_to_image(struc->mlx, "./xpm/mur.xpm", &img_width,
			&img_height);
	struc->sol = mlx_xpm_file_to_image(struc->mlx, "./xpm/grass.xpm",
			&img_width, &img_height);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				mlx_put_image_to_window(struc->mlx, struc->win, struc->mur, x
					* img_width, y * img_width);
			}
			else if (map[y][x] != '\n')
			// if (map[y][x] == '0')
			{
				mlx_put_image_to_window(struc->mlx, struc->win, struc->sol, x
					* img_width, y * img_width);
			}
			x++;
		}
		y++;
	}
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
	mlx_loop(str.mlx);
}
