/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 22:59:43 by david             #+#    #+#             */
/*   Updated: 2019/06/22 21:11:03 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

static int julia_iter(t_fractol *f)
{
    int i;

    i = -1;
    while (++i < f->i_max)
    {
        f->jul->tmp = f->jul->zr;
        f->jul->zr = f->jul->zr * f->jul->zr - f->jul->zi * f->jul->zi + f->jul->cr ;
        f->jul->zi = 2 * f->jul->tmp * f->jul->zi + f->jul->ci ;
        if (f->jul->zr * f->jul->zr + f->jul->zi * f->jul->zi >= 4)
            return (f->psycho == 0 ? i : i + 1 - (log(2) / sqrt(f->jul->zr * f->jul->zr + f->jul->zi * f->jul->zi)) / log(2));
    }
    return (f->psycho == 0 ? i : i + 1 - (log(2) / sqrt(f->jul->zr * f->jul->zr + f->jul->zi * f->jul->zi)) / log(2));
}

void julia(t_fractol *f)
{
    intmax_t x;
    intmax_t y;
    double step_i;
    double step_r;
    
    step_i = (f->max_imag - f->min_imag) / HEIGHT;
    step_r = (f->max_real - f->min_real) / WIDTH;
    x = f->x;
    while (++x < WIDTH + f->x)
    {
        y = f->y;
        while (++y < HEIGHT + f->y)
        {
            f->jul->zi = f->max_imag - step_i * y;
            f->jul->zr = f->min_real + step_r * x;
            put_pxl(f, x - f->x, y - f->y, get_color(f, julia_iter(f)));
        }
    }
    mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}