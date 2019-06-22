/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 18:59:11 by david             #+#    #+#             */
/*   Updated: 2019/06/14 18:30:43 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

int main(int argc, char **argv)
{
    t_fractol *f;

    f = fract_init();
    if (ft_strcmp(argv[1], "mandelbrot") == 0)
        f->fractal = mandelbrot;
    if (ft_strcmp(argv[1], "julia") == 0)
        f->fractal = julia;
    if (ft_strcmp(argv[1], "burningship") == 0)
        f->fractal = burningship;
    if (f->fractal == NULL)
        terminate("Usage <filename> [mandelbrot/julia/burningship]\n");
    
    
    f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "fract'ol");
    f->fractal(f);
    mlx_hook(f->win, 2, 0, key_press, f);
	mlx_hook(f->win, 17, 0, close_x, f);
	mlx_hook(f->win, 6, 0, mouse_move, f);
	mlx_mouse_hook(f->win,  mouse_zoom, f);
    mlx_loop(f->mlx);
    return (0);
}
