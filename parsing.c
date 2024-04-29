/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:41:54 by ahenault          #+#    #+#             */
/*   Updated: 2024/04/12 20:23:30 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	ft_strlen_bis(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

void	flood2(char **map, t_number *number, int y, int x)
{
	if (map[y][x] == 'C')
		number->c--;
	map[y][x] = '1';
	if (map[y][x + 1] && (map[y][x + 1] == 'E'))
		number->e = 0;
	if (map[y][x - 1] && (map[y][x - 1] == 'E'))
		number->e = 0;
	if (map[y + 1][x] && (map[y + 1][x] == 'E'))
		number->e = 0;
	if (map[y - 1][x] && (map[y - 1][x] == 'E'))
		number->e = 0;
	if (map[y + 1][x] && (map[y + 1][x] == '0' || map[y + 1][x] == 'C'))
		flood2(map, number, y + 1, x);
	if (map[y - 1][x] && (map[y - 1][x] == '0' || map[y - 1][x] == 'C'))
		flood2(map, number, y - 1, x);
	if (map[y][x + 1] && (map[y][x + 1] == '0' || map[y][x + 1] == 'C'))
		flood2(map, number, y, x + 1);
	if (map[y][x - 1] && (map[y][x - 1] == '0' || map[y][x - 1] == 'C'))
		flood2(map, number, y, x - 1);
}

void	flood_fill(char **map, t_data *data, t_number number)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				flood2(map, &number, y, x);
				data->player.y = y;
				data->player.x = x;
			}
			x++;
		}
		y++;
	}
	free_tab(map);
	if (number.c != 0 || number.e != 0)
		ft_error(ERROR7, data);
}

char	**copy_map(t_data *data, int nb)
{
	char	**copy;
	int		i;

	i = 0;
	copy = malloc(sizeof(char *) * (nb + 1));
	if (!copy)
		ft_error(ERROR2, data);
	while (data->map.map[i])
	{
		copy[i] = ft_strdup(data->map.map[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	parsing(t_data *data)
{
	t_number	number;
	int			i;
	size_t		size;

	number.c = 0;
	number.p = 0;
	number.e = 0;
	data->player.c = 0;
	i = 0;
	size = ft_strlen_bis(data->map.map[i]);
	if (!size)
		ft_error(ERROR2, data);
	is_closed_by_walls(data);
	while (data->map.map[i])
	{
		count_characters(data->map.map[i], &number, data);
		if (!is_valid_characters(data->map.map[i]))
			ft_error(ERROR3, data);
		if (size != ft_strlen_bis(data->map.map[i]))
			ft_error(ERROR5, data);
		i++;
	}
	if (number.e != 1 || number.p != 1 || number.c < 1)
		ft_error(ERROR4, data);
	flood_fill(copy_map(data, i), data, number);
}
