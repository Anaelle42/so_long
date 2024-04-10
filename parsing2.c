/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:25:36 by ahenault          #+#    #+#             */
/*   Updated: 2024/04/10 20:02:04 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_Bool	check_extension(char *ext)
{
	int	i;

	i = 0;
	while (ext[i])
		i++;
	if (ft_strncmp(".ber", ext + i - 4, 4) != 0)
		return (False);
	return (True);
}

t_Bool	is_valid_characters(char *line)
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

void	count_characters(char *line, t_number *number, t_data *str)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'C')
		{
			number->c++;
			str->c++;
		}
		if (line[i] == 'P')
			number->p++;
		if (line[i] == 'E')
			number->e++;
		i++;
	}
}

void	is_closed_by_walls(t_data *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str->data_map.map[j][i] && str->data_map.map[j][i] != '\n')
	{
		if (str->data_map.map[j][i] != '1')
			ft_error(ERROR6, str);
		i++;
	}
	j++;
	while (str->data_map.map[j])
	{
		i = 0;
		if (str->data_map.map[j][i] && str->data_map.map[j][i] != '1')
			ft_error(ERROR6, str);
		while (str->data_map.map[j][i] && str->data_map.map[j][i] != '\n')
			i++;
		if (str->data_map.map[j][i - 1] && str->data_map.map[j][i - 1] != '1')
			ft_error(ERROR6, str);
		j++;
	}
	i = 0;
	while (str->data_map.map[j - 1][i] && str->data_map.map[j - 1][i] != '\n')
	{
		if (str->data_map.map[j - 1][i] != '1')
			ft_error(ERROR6, str);
		i++;
	}
	str->nb_y = j;
	str->nb_x = i;
}
