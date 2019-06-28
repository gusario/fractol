/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 20:36:42 by david             #+#    #+#             */
/*   Updated: 2019/06/28 06:35:13 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

t_coord			*init_coord(void)
{
	t_coord *j;

	if (!(j = (t_coord*)malloc(sizeof(t_coord))))
		terminate("Malloc error\n");
	j->ci = 0.27105;
	j->cr = -0.7;
	j->zi = 0;
	j->zr = 0;
	j->tmp = 0;
	return (j);
}

t_fractol		*fract_init(void)
{
	t_fractol *f;

	if (!(f = (t_fractol*)malloc(sizeof(t_fractol))))
		terminate("Malloc error\n");
	f->mlx = mlx_init();
	f->img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	f->data_addr = mlx_get_data_addr(f->img, &(f->bpp), &(f->size_line),
	&(f->endian));
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "fract'ol");
	f->mouse_stop = 1;
	f->x_start = -1;
	f->y_start = -1;
	return (f);
}

t_fract_param	*param_init(void)
{
	t_fract_param *f;

	if (!(f = (t_fract_param*)malloc(sizeof(t_fract_param))))
		terminate("Malloc error\n");
	f->i_max = 50;
	f->color_palete = 1;
	f->color_val = 1;
	f->max_imag = 1.5;
	f->min_imag = -1.5;
	f->max_real = 1.0;
	f->min_real = -2.0;
	f->color_max = 0xFFFFFF;
	f->height = HEIGHT;
	f->width = WIDTH;
	f->multi_power = 2;
	return (f);
}
