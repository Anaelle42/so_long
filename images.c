/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:07:41 by ahenault          #+#    #+#             */
/*   Updated: 2024/04/05 17:07:57 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	images(t_data *struc, char **map)
{
	int	x;
	int	y;
	int	img_height;
	int	img_width;

	x = 0;
	y = 0;
	struc->mur = mlx_xpm_file_to_image(struc->mlx, "./xpm/mur.xpm", &img_width,
			&img_height);
	struc->sol = mlx_xpm_file_to_image(struc->mlx, "./xpm/grass.xpm",
			&img_width, &img_height);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			printf("%c", map[y][x]);
			if (map[y][x] == '1')
			{
				mlx_put_image_to_window(struc->mlx, struc->win, struc->mur, x
					* img_width, y * img_width);
			}
			else if (map[y][x] != '\n')
			// if (map[y][x] == '0')
			{
				mlx_put_image_to_window(struc->mlx, struc->win, struc->sol, x
					* img_width, y * img_width);
			}
			x++;
		}
		y++;
	}
}

// str.img = mlx_new_image(str.mlx, 1000, 600);
// str.addr = mlx_get_data_addr(str.img, &str.bits_per_pixel,
//&str.line_length,
// 		&str.endian);
// str.data_map.mur = mlx_xpm_file_to_image(str.mlx, "./xpm/tree.xpm",
// 		&img_width, &img_height);

// images(str, str.data_map.map);
