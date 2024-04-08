/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_la_map_mais_pas_ouf_sauf_celle_de_mael        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:58:55 by ahenault          #+#    #+#             */
/*   Updated: 2024/04/02 17:58:56 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// TODO: load la map, liste chainee ou dyna malloc x2
t_map	load_map(char *file)
{
	t_map data_map;
	int i;
	int fd;
	int nb_line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error(ERROR);
	i = 0;
	nb_line = count_line();
	data_map.map = malloc(sizeof(char *) * nb_line);
	while (i < nb_line)
	{
		data_map.map[i] = get_next_line(fd);
		i++;
	}
	data_map.map[i] = NULL;
	return (data_map);
}