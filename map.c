/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:07:12 by ahenault          #+#    #+#             */
/*   Updated: 2024/04/09 19:24:48 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// TODO: free

void	ft_error(char *error)
{
	printf("Error\n%s\n", error);
	exit(1);
}

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

int	finito(t_data *str)
{
	mlx_destroy_window(str->mlx, str->win);
	mlx_destroy_display(str->mlx);
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
	xpm(&str);
	str.win = mlx_new_window(str.mlx, str.img_width * str.nb_x, str.img_height
			* str.nb_y, "So_long");
	images(&str, str.data_map.map);
	mlx_hook(str.win, KeyPress, KeyPressMask, fonction, &str);
	mlx_hook(str.win, DestroyNotify, StructureNotifyMask, finito, &str);
	mlx_loop(str.mlx);
}
