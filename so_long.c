/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:07:12 by ahenault          #+#    #+#             */
/*   Updated: 2024/06/27 16:06:52 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error(char *error, t_data *data)
{
	ft_printf("Error\n%s\n", error);
	if (data->map.map)
		free_tab(data->map.map);
	exit(1);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	read_and_copy(t_list *tmp, t_list *list, t_data *data, int i)
{
	data->map.map = malloc(sizeof(char *) * (i + 1));
	if (!data->map.map)
	{
		ft_lstclear(&list, free);
		ft_error(ERROR9, data);
	}
	i = 0;
	tmp = list;
	while (list)
	{
		data->map.map[i] = ft_strdup(list->content);
		if (!data->map.map[i])
		{
			ft_lstclear(&list, free);
			ft_error(ERROR9, data);
		}
		list = list->next;
		i++;
	}
	ft_lstclear(&tmp, free);
	data->map.map[i] = NULL;
}

void	read_map(char *file, t_data *data)
{
	t_list	*list;
	t_list	*tmp;
	int		fd;
	int		i;
	char	*line;

	line = NULL;
	list = NULL;
	tmp = NULL;
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error(ERROR2, data);
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_lstadd_back(&list, ft_lstnew((void *)line));
		line = get_next_line(fd);
		i++;
	}
	if (close(fd) == -1)
		ft_error(ERROR2, data);
	read_and_copy(tmp, list, data, i);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.map.map = NULL;
	if (argc != 2 || check_extension(argv[1]) == 0)
		ft_error(ERROR1, &data);
	read_map(argv[1], &data);
	parsing(&data);
	data.win = 0;
	data.player.movements = 0;
	data.player.score = 0;
	data.mlx = mlx_init();
	if (!data.mlx)
		ft_error(ERROR8, &data);
	load_xpm_images(&data);
	data.win = mlx_new_window(data.mlx, data.img.img_width * data.map.width,
			data.img.img_height * data.map.height, "Banana schtroumpf");
	if (!data.win)
	{
		ft_printf("Error\nMlx Error\n");
		on_destroy(&data);
	}
	display_images(&data);
	mlx_hook(data.win, KeyPress, KeyPressMask, key_hook, &data);
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, on_destroy, &data);
	mlx_loop(data.mlx);
}
