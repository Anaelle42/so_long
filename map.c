/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:07:12 by ahenault          #+#    #+#             */
/*   Updated: 2024/04/10 20:04:15 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// TODO: free

void	ft_error(char *error, t_data *str)
{
	printf("Error\n%s\n", error);
	if (str->data_map.map)
		free_stp(str->data_map.map);
	exit(1);
}
void	free_stp(char **tab)
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

t_map	load_map(char *file, t_data *str)
{
	t_list	*list;
	t_list	*tmp;
	t_map	map;
	int		fd;
	int		i;
	char	*line;

	line = NULL;
	list = NULL;
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error(ERROR2, str);
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_lstadd_back(&list, ft_lstnew((void *)line));
		line = get_next_line(fd);
		i++;
	}
	map.map = malloc(sizeof(char *) * (i + 1));
	i = 0;
	tmp = list;
	while (list)
	{
		map.map[i] = ft_strdup(list->content);
		list = list->next;
		i++;
	}
	ft_lstclear(&tmp, free);
	map.map[i] = NULL;
	return (map);
}

int	finito(t_data *str)
{
	mlx_destroy_image(str->mlx, str->mur);
	mlx_destroy_image(str->mlx, str->sol);
	mlx_destroy_image(str->mlx, str->porte);
	mlx_destroy_image(str->mlx, str->coin);
	mlx_destroy_image(str->mlx, str->perso);
	mlx_destroy_window(str->mlx, str->win);
	mlx_destroy_display(str->mlx);
	free_stp(str->data_map.map);
	free(str->mlx);
	exit(1);
	return (0);
}

int	main(int argc, char **argv)
{
	int		i;
	t_data	str;

	i = 0;
	if (argc != 2 || check_extension(argv[1]) == 0)
		ft_error(ERROR1, &str);
	str.data_map = load_map(argv[1], &str);
	parsing(&str);
	while (str.data_map.map[i])
	{
		printf("%s", str.data_map.map[i]);
		i++;
	}
	// free_stp(str.data_map.map);
	str.compte_mvts = 0;
	str.score = 0;
	str.mlx = mlx_init();
	xpm(&str);
	str.win = mlx_new_window(str.mlx, str.img_width * str.nb_x, str.img_height
			* str.nb_y, "So_long");
	images(&str, str.data_map.map);
	mlx_hook(str.win, KeyPress, KeyPressMask, fonction, &str);
	mlx_hook(str.win, DestroyNotify, StructureNotifyMask, finito, &str);
	mlx_loop(str.mlx);
}
