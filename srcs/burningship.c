/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 15:39:07 by srobert-          #+#    #+#             */
/*   Updated: 2019/06/22 19:17:21 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

static int burningship_iter(t_fractol *f)
{
    int i;

    i = -1;

    while (++i < f->i_max)
    {
        f->ship->tmp = f->ship->zr;
        f->ship->zr = f->ship->zr * f->ship->zr - f->ship->zi * f->ship->zi + f->ship->cr;
        f->ship->zi = 2 * fabs(f->ship->tmp * f->ship->zi) + f->ship->ci;
        if (f->ship->zr * f->ship->zr + f->ship->zi * f->ship->zi > 1.0E16)
            return (f->psycho == 0 ? i : i + 1 - (log(2) / sqrt(f->ship->zr * f->ship->zr + f->ship->zi * f->ship->zi)) / log(2));
    }
    return (f->psycho == 0 ? i : i + 1 - (log(2) / sqrt(f->ship->zr * f->ship->zr + f->ship->zi * f->ship->zi)) / log(2));
}

void burningship(t_fractol *f)
{
    intmax_t x;
    intmax_t y;

    x = f->x;
    while (++x < WIDTH + f->x)
    {
        y = f->y;
        while (++y < HEIGHT + f->y)
        {
            f->ship->zi = 0;
            f->ship->zr = 0;
            f->ship->cr = 1.5 * ((double)x - WIDTH / 2) / (0.5 * f->zoom * WIDTH);
            f->ship->ci = ((double)y - HEIGHT / 2) / (0.5 * f->zoom * HEIGHT);
            put_pxl(f, x - f->x, y - f->y, get_color(f, burningship_iter(f)));
            
        }
    }
    mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}
