/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 19:32:47 by srobert-          #+#    #+#             */
/*   Updated: 2019/06/22 20:53:15 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

int	close_x(void)
{
	exit(0);
}

int	key_press(int key, t_fractol *f)
{
	if (key == MAIN_PAD_ESC)
		exit(0);
	if (key == MAIN_PAD_W)
    {
        f->max_imag += (f->max_imag - f->min_imag) * 0.1;
        f->min_imag += (f->max_imag - f->min_imag) * 0.1;
    }
    if (key == MAIN_PAD_S)
    {
        f->max_imag -= (f->max_imag - f->min_imag) * 0.1;
        f->min_imag -= (f->max_imag - f->min_imag) * 0.1;
    }
    if (key == MAIN_PAD_A)
    {
        f->max_real -= (f->max_real - f->min_real) * 0.1;
        f->min_real -= (f->max_real - f->min_real) * 0.1;
    }
    if (key == MAIN_PAD_D)
    {
        f->max_real += (f->max_real - f->min_real) * 0.1;
        f->min_real += (f->max_real - f->min_real) * 0.1;
    }
    if (key == MAIN_PAD_PLUS)
        f->i_max += 5;
    if (key == MAIN_PAD_MINUS && f->i_max > 5)
        f->i_max -= 5;
    if (key == MAIN_PAD_F)
        f->psycho = !f->psycho;
    if (key == MAIN_PAD_X)
        f->color_val--;
    if (key == MAIN_PAD_C)
        f->color_val++;      
    f->fractal(f);
    return (0);
}
int mouse_move(int x, int y, t_fractol *f)
{
    if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT || f->mouse_stop == 1)   
        return (0);
    f->jul->ci = (y - HEIGHT / 2) * 0.002;
    f->jul->cr = (x - WIDTH / 2) * 0.002;
    f->fractal(f);
    return (0);
}

int mouse_zoom(int key, int x, int y, t_fractol *f)
{
    double re;
    double im;

    im = (f->max_imag - f->min_imag) * 0.1;
    re = (f->max_real - f->min_real) * 0.1;
    
    if (key == SCROLL_UP)
    {
        f->min_imag -= im * (1.0 - (double)y / HEIGHT);
        f->max_imag += im * ((double)y / HEIGHT);
        f->min_real -= re * ((double)x / WIDTH);
        f->max_real += re * (1.0 - (double)x / WIDTH);
    }
    
    if (key == SCROLL_DOWN)
    {
        f->min_imag += im * (1.0 - (double)y / HEIGHT);
        f->max_imag -= im * ((double)y / HEIGHT);
        f->min_real += re * ((double)x / WIDTH);     
        f->max_real -= re * (1.0 - (double)x / WIDTH);
        
    }   
    f->fractal(f);
    return (0);
}
