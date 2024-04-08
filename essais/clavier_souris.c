/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clavier_souris.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:54:36 by ahenault          #+#    #+#             */
/*   Updated: 2024/03/27 17:24:55 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*img2;

}			t_vars;

int	touche(int keycode, t_vars *vars)
{
	static int	x;
	static int	y;

	printf("touche = %i \n", keycode);
	if (keycode == 32)
	{
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, x, y);
		x = x + 85;
		if (x >= 680)
		{
			x = 0;
			y += 85;
		}
	}
	if (keycode == 99)
	{
		mlx_mouse_get_pos(vars->mlx, vars->win, &x, &y);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, x, y);
	}
	return (0);
}

int	mouse(int mouse, int x, int y, t_vars *vars)
{
	static int	bas;

	if (mouse == 1)
	{
		printf("gauche = %i \n", mouse);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img2, x, y);
	}
	if (mouse == 3)
	{
		printf("droite = %i \n", mouse);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, x, y);
	}
	if (mouse == 5)
	{
		mlx_mouse_move(vars->mlx, vars->win, 0, bas);
		bas += 85;
	}
	if (mouse == 4)
	{
		mlx_mouse_move(vars->mlx, vars->win, 0, bas);
		bas -= 85;
	}
	return (0);
}

int	main(void)
{
	t_vars	vars;
	int		img_width;
	int		img_height;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 680, 510, "Hello world!");
	vars.img = mlx_xpm_file_to_image(vars.mlx, "./xpm/chat.xpm", &img_width,
			&img_height);
	vars.img2 = mlx_xpm_file_to_image(vars.mlx, "./xpm/truc.xpm", &img_width,
			&img_height);
	mlx_key_hook(vars.win, touche, &vars);
	mlx_mouse_move(vars.mlx, vars.win, 0, 0);
	mlx_mouse_hook(vars.win, mouse, &vars);
	mlx_loop(vars.mlx);
}

/*
mlx_hook(vars.win, 2, 1L << 0, ft_close, &vars);
= mlx_key_hook(vars.win, ft_close, &vars); 
alias of mlx_hook on key up event
*/
