/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:55:57 by ahenault          #+#    #+#             */
/*   Updated: 2024/06/27 15:28:34 by ahenault         ###   ########.fr       */
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
# define ERROR8 "Mlx error"
# define ERROR9 "Malloc error"

typedef enum t_bool
{
	FALSE = 0,
	TRUE = 1
}				t_bool;

typedef struct s_number
{
	int			c;
	int			p;
	int			e;
}				t_number;

typedef struct s_map
{
	char		**map;
	int			width;
	int			height;
}				t_map;

typedef struct s_image
{
	int			img_height;
	int			img_width;
	void		*wall;
	void		*floor;
	void		*exit;
	void		*player;
	void		*collectible;
}				t_image;

typedef struct s_player
{
	int			x;
	int			y;
	int			c;
	int			score;
	int			movements;
}				t_player;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_image		img;
	t_player	player;
}				t_data;

void			free_tab(char **tab);
void			display_images(t_data *data);
void			ft_error(char *error, t_data *str);
void			load_xpm_images(t_data *struc);
int				on_destroy(t_data *str);
int				key_hook(int key, t_data *data);
void			parsing(t_data *str);
t_bool			check_extension(char *ext);
t_bool			is_valid_characters(char *line);
void			count_characters(char *line, t_number *number, t_data *str);
void			is_closed_by_walls(t_data *str);

#endif