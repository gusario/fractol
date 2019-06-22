/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 14:19:53 by david             #+#    #+#             */
/*   Updated: 2019/06/22 20:45:58 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"


static int mandelbrot_iter(t_fractol *f)
{
    int i;

    i = -1;

    while (++i < f->i_max)
    {
        f->mdb->tmp = f->mdb->zr;
        f->mdb->zr = f->mdb->zr * f->mdb->zr - f->mdb->zi * f->mdb->zi + f->mdb->cr;
        f->mdb->zi = 2 * f->mdb->tmp * f->mdb->zi + f->mdb->ci;
        if (f->mdb->zr * f->mdb->zr + f->mdb->zi * f->mdb->zi > 4)
            //return (i);
             return (f->psycho == 0 ? i : i + 1 - (log(2) / sqrt(f->mdb->zr * f->mdb->zr + f->mdb->zi * f->mdb->zi)) / log(2));
    }
    //return (i);
      return (f->psycho == 0 ? i : i + 1 - (log(2) / sqrt(f->mdb->zr * f->mdb->zr + f->mdb->zi * f->mdb->zi)) / log(2));
}

void mandelbrot(t_fractol *f)
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
            f->mdb->zi = 0;
            f->mdb->zr = 0;
            f->mdb->ci = f->max_imag - step_i * y ;
            f->mdb->cr = f->min_real + step_r * x; 
            put_pxl(f, x - f->x, y - f->y, get_color(f, mandelbrot_iter(f)));
            
        }
    }
    mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}