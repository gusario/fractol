/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 19:01:56 by david             #+#    #+#             */
/*   Updated: 2019/09/06 18:06:22 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errno.h"
#include "fract.h"

void	swap_fractal(int key, t_fract_param *f)
{
	if (key == MAIN_PAD_1)
		f->name = 1;
	if (key == MAIN_PAD_2)
		f->name = 2;
	if (key == MAIN_PAD_3)
		f->name = 3;
	if (key == MAIN_PAD_4)
		f->name = 4;
	if (key == MAIN_PAD_5)
		f->name = 5;
	if (key == MAIN_PAD_6)
		f->name = 6;
	if (key == MAIN_PAD_7)
		f->name = 7;
	if (key == MAIN_PAD_8)
		f->name = 8;
	if (key == MAIN_PAD_1 || key == MAIN_PAD_2 ||
	key == MAIN_PAD_3 || key == MAIN_PAD_4 || key == MAIN_PAD_5 ||
	key == MAIN_PAD_6 || key == MAIN_PAD_7 || key == MAIN_PAD_8)
		reset(MAIN_PAD_F, f);
}

int		chill(int key)
{
	if (key != MAIN_PAD_A && key != MAIN_PAD_C && key != MAIN_PAD_D &&
	key != MAIN_PAD_ESC && key != MAIN_PAD_F && key != MAIN_PAD_LESS &&
	key != MAIN_PAD_MINUS && key != MAIN_PAD_MORE && key != MAIN_PAD_P &&
	key != MAIN_PAD_PLUS && key != MAIN_PAD_S && key != MAIN_PAD_W &&
	key != MAIN_PAD_X && key != MAIN_PAD_1 && key != MAIN_PAD_2 &&
	key != MAIN_PAD_3 && key != MAIN_PAD_4 && key != MAIN_PAD_5 &&
	key != MAIN_PAD_6 && key != MAIN_PAD_7 && key != MAIN_PAD_8)
		return (1);
	else
		return (0);
}

void	text(t_fractol *f, t_fract_param *par)
{
	char *str;

	str = ft_itoa(par->i_max);
	mlx_string_put(f->mlx, f->win, 20, 20, 0X000000, "ITERATIONS:");
	mlx_string_put(f->mlx, f->win, 140, 20, 0X000000, str);
	mlx_string_put(f->mlx, f->win, 20, 60, 0X000000, "NAME: ");
	if (par->name == 1)
		mlx_string_put(f->mlx, f->win, 80, 60, 0X000000, "Mandelbrot");
	else if (par->name == 2)
		mlx_string_put(f->mlx, f->win, 80, 60, 0X000000, "Julia");
	else if (par->name == 3)
		mlx_string_put(f->mlx, f->win, 80, 60, 0X000000, "Burningship");
	else if (par->name == 4)
		mlx_string_put(f->mlx, f->win, 80, 60, 0X000000, "Dickship");
	else if (par->name == 5)
		mlx_string_put(f->mlx, f->win, 80, 60, 0X000000, "Multibrot");
	else if (par->name == 6)
		mlx_string_put(f->mlx, f->win, 80, 60, 0X000000, "Multi_Julia");
	else if (par->name == 7)
		mlx_string_put(f->mlx, f->win, 80, 60, 0X000000, "Antimandelbrot");
	else if (par->name == 8)
		mlx_string_put(f->mlx, f->win, 80, 60, 0X000000, "Biomorph");
	free(str);
}

void	terminate(char *s)
{
	if (ft_strcmp(s, "usage") == 0)
		s = "Usage <filename> \n[\n1. mandelbrot\n2.julia\n3. burningship\
		\n4. dickship\n5. multibrot\n6. multijulia\n7. antimandel\
		\n8. biomorph\n]\n";
	if (errno == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	sleep(100000);
	exit(1);
}
