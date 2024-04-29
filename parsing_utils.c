/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:25:36 by ahenault          #+#    #+#             */
/*   Updated: 2024/04/12 19:06:19 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_bool	check_extension(char *ext)
{
	int	i;

	i = 0;
	while (ext[i])
		i++;
	if (ft_strncmp(".ber", ext + i - 4, 4) != 0)
		return (False);
	return (True);
}

t_bool	is_valid_characters(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'C' && line[i] != 'P'
			&& line[i] != 'E')
			return (False);
		i++;
	}
	return (True);
}

void	count_characters(char *line, t_number *number, t_data *data)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'C')
		{
			number->c++;
			data->player.c++;
		}
		if (line[i] == 'P')
			number->p++;
		if (line[i] == 'E')
			number->e++;
		i++;
	}
}

void	is_first_line_closed_by_walls(t_data *data)
{
	int	i;

	i = 0;
	while (data->map.map[0][i] && data->map.map[0][i] != '\n')
	{
		if (data->map.map[0][i] != '1')
			ft_error(ERROR6, data);
		i++;
	}
	data->map.width = i;
}

void	is_closed_by_walls(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	is_first_line_closed_by_walls(data);
	while (data->map.map[j])
	{
		i = 0;
		if (data->map.map[j][i] && data->map.map[j][i] != '1')
			ft_error(ERROR6, data);
		while (data->map.map[j][i] && data->map.map[j][i] != '\n')
			i++;
		if (data->map.map[j][i - 1] && data->map.map[j][i - 1] != '1')
			ft_error(ERROR6, data);
		j++;
	}
	i = 0;
	while (data->map.map[j - 1][i] && data->map.map[j - 1][i] != '\n')
	{
		if (data->map.map[j - 1][i] != '1')
			ft_error(ERROR6, data);
		i++;
	}
	data->map.height = j;
}
