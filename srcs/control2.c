/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 05:54:09 by srobert-          #+#    #+#             */
/*   Updated: 2019/06/28 07:35:21 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

int			close_x(void)
{
	exit(0);
}

int			mouse_move(int x, int y, void *param)
{
	void **mass;

	mass = (void**)param;
	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT ||
	((t_fractol*)(mass[2]))->mouse_stop == 0)
		return (0);
	((t_coord*)(mass[3]))->ci = (y - HEIGHT / 2) * 0.002;
	((t_coord*)(mass[3]))->cr = (x - WIDTH / 2) * 0.002;
	if (((t_fract_param*)mass[0])->name == 1 ||
	((t_fract_param*)mass[0])->name == 3 || ((t_fract_param*)mass[0])->name == 4
	|| ((t_fract_param*)mass[0])->name == 5)
		return (0);
	draw_fractal(mass[1], mass[2], mass[0], mass[3]);
	return (0);
}

static int	mouse_zoom(int key, int x, int y, void **mass)
{
	double	re;
	double	im;

	im = (((t_fract_param*)(mass[0]))->max_imag -
		((t_fract_param*)(mass[0]))->min_imag) * 0.1;
	re = (((t_fract_param*)(mass[0]))->max_real -
		((t_fract_param*)(mass[0]))->min_real) * 0.1;
	if (key == SCROLL_UP)
	{
		((t_fract_param*)(mass[0]))->min_imag -= im * ((double)y / HEIGHT);
		((t_fract_param*)(mass[0]))->max_imag += im * (1 - (double)y / HEIGHT);
		((t_fract_param*)(mass[0]))->min_real -= re * ((double)x / WIDTH);
		((t_fract_param*)(mass[0]))->max_real += re * (1 - (double)x / WIDTH);
	}
	if (key == SCROLL_DOWN)
	{
		((t_fract_param*)(mass[0]))->min_imag += im * ((double)y / HEIGHT);
		((t_fract_param*)(mass[0]))->max_imag -= im * (1 - (double)y / HEIGHT);
		((t_fract_param*)(mass[0]))->min_real += re * ((double)x / WIDTH);
		((t_fract_param*)(mass[0]))->max_real -= re * (1 - (double)x / WIDTH);
	}
	return (0);
}

int			mouse_manage(int key, int x, int y, void *param)
{
	void	**mass;

	mass = (void**)param;
	if (key != SCROLL_DOWN && key != SCROLL_UP && key != RIGHT_MOUSE)
		return (0);
	mouse_zoom(key, x, y, mass);
	if (key == RIGHT_MOUSE)
		((t_fractol*)(mass[2]))->mouse_stop =
		!((t_fractol*)(mass[2]))->mouse_stop;
	draw_fractal(mass[1], mass[2], mass[0], mass[3]);
	return (0);
}
