/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 14:27:59 by david             #+#    #+#             */
/*   Updated: 2019/06/22 17:46:13 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

void put_pxl(t_fractol *f, int x, int y, unsigned int color)
{
    int i;
    
    i = x * 4 + y * f->size_line;
    f->data_addr[i] = color;
    f->data_addr[++i] = color >> 8;
    f->data_addr[++i] = color >> 16;
}

unsigned int get_color(t_fractol *f, int a)
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned int c;
    
    if (a == f->i_max)
        return (f->color_max);
    r = (a * 5) * f->color_val;
    g = (255 - a * 10) * f->color_val;
    b = (255 - a * 2) * f->color_val;
    c = (r << 16) + (g << 8) + b;

    // r = (unsigned char)(sin(0.016 * a + 4) * 230 + 25) * f->color_val;
    // g = (unsigned char)(sin(0.013 * a + 2) * 230 + 25) * f->color_val;
    // b = (unsigned char)(sin(0.01 * a + 1) * 230 + 25) * f->color_val;
    // c = (r << 16) + (g << 8) + b;
    return (c);
}