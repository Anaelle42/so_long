/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:28:06 by ahenault          #+#    #+#             */
/*   Updated: 2025/03/20 15:49:54 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free_gnl(t_list *list, char *line, int fd, t_data *data)
{
	ft_lstclear(&list, free);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	ft_error(ERROR9, data);
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

	list = NULL;
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error(ERROR2, data);
	line = get_next_line(fd);
	while (line != NULL)
	{
		tmp = ft_lstnew((void *)line);
		if (!tmp)
			return (ft_free_gnl(list, line, fd, data));
		ft_lstadd_back(&list, tmp);
		line = get_next_line(fd);
		i++;
	}
	if (close(fd) == -1)
		ft_error(ERROR2, data);
	read_and_copy(tmp, list, data, i);
}
