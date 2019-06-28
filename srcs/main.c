/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 18:59:11 by david             #+#    #+#             */
/*   Updated: 2019/06/28 06:54:50 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

static int	whoami(char *argv)
{
	if (ft_strcmp(argv, "mandelbrot") == 0)
		return (1);
	else if (ft_strcmp(argv, "julia") == 0)
		return (2);
	else if (ft_strcmp(argv, "burningship") == 0)
		return (3);
	else if (ft_strcmp(argv, "dickship") == 0)
		return (4);
	else if (ft_strcmp(argv, "multibrot") == 0)
		return (5);
	else if (ft_strcmp(argv, "multijulia") == 0)
		return (6);
	else if (ft_strcmp(argv, "antimandel") == 0)
		return (7);
	else if (ft_strcmp(argv, "biomorph") == 0)
		return (8);
	else
		return (-1);
}

int			main(int argc, char **argv)
{
	t_cl_str		cl;
	t_fract_param	*par;
	void			*mass[4];

	if (argc != 2)
		terminate("usage");
	par = param_init();
	par->name = whoami(argv[1]);
	if (par->name == -1)
		terminate("usage");
	prepare_cl(&cl);
	mass[0] = par;
	mass[1] = &(cl);
	mass[2] = fract_init();
	mass[3] = init_coord();
	draw_fractal(mass[1], mass[2], mass[0], mass[3]);
	mlx_hook(((t_fractol*)(mass[2]))->win, 2, 0, key_press, mass);
	mlx_hook(((t_fractol*)(mass[2]))->win, 17, 0, close_x, mass);
	mlx_hook(((t_fractol*)(mass[2]))->win, 6, 0, mouse_move, mass);
	mlx_mouse_hook(((t_fractol*)(mass[2]))->win, mouse_manage, mass);
	mlx_loop(((t_fractol*)(mass[2]))->mlx);
	free(mass);
	return (0);
}
