/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 19:32:47 by srobert-          #+#    #+#             */
/*   Updated: 2019/09/06 18:06:12 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

void		reset(int key, t_fract_param *f)
{
	if (key == MAIN_PAD_ESC)
		exit(0);
	if (key == MAIN_PAD_F)
	{
		f->i_max = 50;
		f->color_palete = 1;
		f->color_val = 1;
		f->max_imag = 1.5;
		f->min_imag = -1.5;
		f->max_real = 1.0;
		f->min_real = -2.0;
	}
}

static void	move(int key, t_fract_param *f)
{
	double	re;
	double	im;

	im = f->max_imag - f->min_imag;
	re = f->max_real - f->min_real;
	if (key == MAIN_PAD_A)
	{
		f->max_real -= re * 0.1;
		f->min_real -= re * 0.1;
	}
	if (key == MAIN_PAD_D)
	{
		f->max_real += re * 0.1;
		f->min_real += re * 0.1;
	}
	if (key == MAIN_PAD_W)
	{
		f->max_imag -= im * 0.1;
		f->min_imag -= im * 0.1;
	}
	if (key == MAIN_PAD_S)
	{
		f->max_imag += im * 0.1;
		f->min_imag += im * 0.1;
	}
}

int			key_press(int key, void *param)
{
	void **mass;

	mass = (void**)param;
	if (chill(key) == 1)
		return (0);
	move(key, mass[0]);
	reset(key, mass[0]);
	swap_fractal(key, mass[0]);
	if (key == MAIN_PAD_PLUS)
		((t_fract_param*)(mass[0]))->i_max += 5;
	if (key == MAIN_PAD_MINUS && ((t_fract_param*)(mass[0]))->i_max > 1)
		((t_fract_param*)(mass[0]))->i_max -= 5;
	if (key == MAIN_PAD_X)
		((t_fract_param*)(mass[0]))->color_val--;
	if (key == MAIN_PAD_C)
		((t_fract_param*)(mass[0]))->color_val++;
	if (key == MAIN_PAD_P)
		((t_fract_param*)(mass[0]))->color_palete =
		!((t_fract_param*)(mass[0]))->color_palete;
	if (key == MAIN_PAD_MORE)
		((t_fract_param*)(mass[0]))->multi_power++;
	if (key == MAIN_PAD_LESS)
		((t_fract_param*)(mass[0]))->multi_power--;
	draw_fractal(mass[1], mass[2], mass[0], mass[3]);
	return (0);
}
