/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brouillon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:07:12 by ahenault          #+#    #+#             */
/*   Updated: 2024/04/04 18:02:12 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#ifndef SCALE
# define SCALE 1
#endif

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*img2;
	void	*img3;
	int		persox;
	int		persoy;
}			t_data;

int	count_line(void)
{
	int	fd;
	int	nb_line;

	nb_line = 0;
	fd = open("map.ber", O_RDONLY);
	if (fd == -1)
		return (0);
	while (get_next_line(fd) > 0)
	{
		nb_line++;
	}
	close(fd);
	return (nb_line);
}

char	**load_map(void)
{
	char	**map;
	int		i;
	int		fd;
	int		nb_line;

	fd = open("map.ber", O_RDONLY);
	if (fd == -1)
		return (0);
	i = 0;
	nb_line = count_line();
	map = malloc(sizeof(char *) * nb_line);
	while (i < nb_line)
	{
		map[i] = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	return (map);
}

void	images(t_data struc, char **map)
{
	int	x;
	int	y;
	int	img_height;
	int	img_width;

	x = 0;
	y = 0;
	struc.img = mlx_xpm_file_to_image(struc.mlx, "./tree.xpm", &img_width,
			&img_height);
	struc.img2 = mlx_xpm_file_to_image(struc.mlx, "./snow.xpm", &img_width,
			&img_height);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				mlx_put_image_to_window(struc.mlx, struc.win, struc.img, x
					* img_width * SCALE, y * img_height * SCALE);
			}
			else if (map[y][x] != '\n')
			// if (map[y][x] == '0')
			{
				mlx_put_image_to_window(struc.mlx, struc.win, struc.img2, x
					* img_width * SCALE, y * img_height * SCALE);
			}
			x++;
		}
		y++;
	}
}

int	main(void)
{
	t_data	struc;
	char	**map;
	void	*mlx;
	void	*win;

	// int		i;
	map = load_map();
	// i = 0;
	// while (i < 5)
	// {
	// 	printf("%s", map[i]);
	// 	i++;
	// }
	struc.mlx = mlx_init();
	struc.win = mlx_new_window(struc.mlx, 1000, 425, "(**)");
	images(struc, map);
	// mlx_key_hook(struc.win, fonction, &struc);
	// perso(struc, map);
	mlx_loop(struc.mlx);
}

/*char	**load_map(void)
{
	char	**map;
	int		i;
	int		fd;

	map = NULL;
	fd = open("map.ber", O_RDONLY);
	if (fd == -1)
		return (0);
	i = 0;
	while (map[i])
	{
		map[i] = ft_strjoin(map[i], get_next_line(fd));
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}*/
void	xpm(t_data *str)
{
	str->wall = mlx_xpm_file_to_image(str->mlx, "./xpm/tree.xpm",
			&str->wall->img_width, &str->wall->img_height);
	str->sol = mlx_xpm_file_to_image(str->mlx, "./xpm/snow.xpm",
			&str->sol->img_width, &str->sol->img_height);
}

void	images(t_data *struc, char **map)
{
	int x;
	int y;

	x = 0;
	y = 0;
	// t_image *wall;
	// wall = malloc(sizeof(t_image));
	// struc->wall = wall;
	// t_image *sol;
	// sol = malloc(sizeof(t_image));
	// struc->sol = sol;
	// xpm(struc);
	struc->wall->img = mlx_xpm_file_to_image(struc->mlx, "./xpm/tree.xpm",
			&struc->wall->img_width, &struc->wall->img_height);
	struc->sol->img = mlx_xpm_file_to_image(struc->mlx, "./xpm/snow.xpm",
			&struc->sol->img_width, &struc->sol->img_height);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				mlx_put_image_to_window(struc->mlx, struc->win,
					struc->wall->img, x * struc->wall->img_width, y
					* struc->wall->img_height);
			}
			else if (map[y][x] == '0')
			{
				mlx_put_image_to_window(struc->mlx, struc->win, struc->sol->img,
					x * struc->sol->img_width, y * struc->sol->img_height);
			}
			x++;
		}
		y++;
	}
}