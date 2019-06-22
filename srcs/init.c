/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 20:36:42 by david             #+#    #+#             */
/*   Updated: 2019/06/22 19:25:31 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

static t_coord *init_mandel()
{
    t_coord *m;
    
    if (!(m = (t_coord*)malloc(sizeof(t_coord))))
        terminate("Malloc error\n");
    m->ci = 0;
    m->cr = 0;
    m->zi = 0;
    m->zr = 0;
    m->tmp = 0;
    return(m);  
}

static t_coord *init_burningship()
{
    t_coord *m;
    
    if (!(m = (t_coord*)malloc(sizeof(t_coord))))
        terminate("Malloc error\n");
    m->ci = 0;
    m->cr = 0;
    m->zi = 0;
    m->zr = 0;
    m->tmp = 0;
    return(m);  
}

static t_coord *init_julia()
{
    t_coord *j;
    
    if (!(j = (t_coord*)malloc(sizeof(t_coord))))
        terminate("Malloc error\n");
    j->ci = 0;
    j->cr = 0;
    j->zi = 0;
    j->zr = 0;
    j->tmp = 0;
    return(j);
}

t_fractol *fract_init()
{
    t_fractol *f;
    if(!(f = (t_fractol*)malloc(sizeof(t_fractol))))
        terminate("Malloc error\n");
    f->x = -1;
    f->y = -1;
    f->z = 150;
    f->option_x = WIDTH / 2;
    f->option_y = HEIGHT / 2;
    f->color_max = 0X000000;
    f->mlx = mlx_init();
    f->i_max = 40;
    f->mouse_stop = 0;
    f->zoom = 0.7;
    f->psycho = 0;
    f->color_val = 1;
    f->max_imag = 1.5;
    f->min_imag = -1.5;
    f->max_real = 1.0;
    f->min_real = -2.0;
    f->img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
    f->data_addr = mlx_get_data_addr(f->img, &(f->bpp), &(f->size_line), &(f->endian));
    f->jul = init_julia();
    f->mdb = init_mandel();
    f->ship = init_burningship();
    return(f);
}