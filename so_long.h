/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:55:57 by ahenault          #+#    #+#             */
/*   Updated: 2024/04/09 19:22:57 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"

# define ERROR1 "The parameter isn't a .ber extension"
# define ERROR2 "Can't open the map"
# define ERROR3 "Invalid characters in the map"
# define ERROR4 "The map does not contain 1P, 1E and at least 1C"
# define ERROR5 "The map isn't rectangular"
# define ERROR6 "The map isn't surrounded by walls"
# define ERROR7 "No valid path"

# ifndef BOOL
#  define BOOL
typedef enum t_Bool
{
	FALSE = 0,
	TRUE = 1
}			t_Bool;
# endif

typedef struct s_map
{
	char	**map;

}			t_map;

typedef struct s_number
{
	int		c;
	int		p;
	int		e;
}			t_number;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		img_height;
	int		img_width;
	void	*img;
	void	*mur;
	void	*sol;
	void	*coin;
	void	*porte;
	void	*perso;
	int		x;
	int		c;
	int		y;
	t_map	data_map;
	int		nb_y;
	int		nb_x;
	int		compte_mvts;

}			t_data;

void		images(t_data *struc, char **map);
void		ft_error(char *error);
void		xpm(t_data *struc);
int			finito(t_data *str);
int			fonction(int key, t_data *str);
void		parsing(t_data *str);
t_Bool		check_extension(char *ext);
t_Bool		is_valid_characters(char *line);
void		count_characters(char *line, t_number *number, t_data *str);
void		is_closed_by_walls(t_data *str);

#endif