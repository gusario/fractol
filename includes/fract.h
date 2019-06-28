/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 07:08:53 by srobert-          #+#    #+#             */
/*   Updated: 2019/06/28 08:07:37 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_H

# define FRACT_H

# define WIDTH 1000
# define HEIGHT 1000

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "mlx.h"
# include <inttypes.h>
# include "../libft/libft.h"
# include "OpenCL/cl.h"

# define MAIN_PAD_ESC       53
# define MAIN_PAD_W         13
# define MAIN_PAD_S         1
# define MAIN_PAD_A         0
# define MAIN_PAD_D         2
# define MAIN_PAD_F         3
# define MAIN_PAD_X         7
# define MAIN_PAD_C         8
# define MAIN_PAD_PLUS      24
# define MAIN_PAD_MINUS     27
# define SCROLL_UP          4
# define SCROLL_DOWN        5
# define MAIN_PAD_P         35
# define RIGHT_MOUSE        2
# define MAIN_PAD_MORE      47
# define MAIN_PAD_LESS      43
# define MAIN_PAD_1			18
# define MAIN_PAD_2			19
# define MAIN_PAD_3			20
# define MAIN_PAD_4			21
# define MAIN_PAD_5			23
# define MAIN_PAD_6			22
# define MAIN_PAD_7			26
# define MAIN_PAD_8			28

typedef struct	s_coord
{
	double zr;
	double zi;
	double cr;
	double ci;
	double tmp;
}				t_coord;

typedef struct	s_fractol
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*data_addr;
	int		size_line;
	int		bpp;
	int		endian;
	int		mouse_stop;
	int		x_start;
	int		y_start;
}				t_fractol;

typedef struct	s_fract_param
{
	double			max_imag;
	double			min_imag;
	double			max_real;
	double			min_real;
	int				i_max;
	int				name;
	int				color_val;
	unsigned int	color_max;
	int				height;
	int				width;
	int				color_palete;
	int				multi_power;
}				t_fract_param;

typedef struct	s_cl_str
{
	cl_device_id		device;
	cl_context			context;
	cl_program			program;
	cl_kernel			kernel;
	cl_command_queue	queue;
	cl_int				i;
	cl_int				err;
	size_t				local_size;
	size_t				global_size;
	cl_program			mandel;
}				t_cl_str;

typedef struct	s_cl_prep
{
	cl_platform_id	platf;
	cl_uint			num_platforms;
	cl_uint			dev;
	int				ret;
	cl_program		program;
	FILE			*fp;
	const char		*filename;
	size_t			source_size;
	char			*source_str;
}				t_cl_prep;

void			terminate(char *s);
t_fractol		*fract_init();
int				close_x(void);
int				key_press(int key, void *param);
int				mouse_move(int x, int y, void *param);
int				mouse_manage(int key, int x, int y, void *param);
void			text(t_fractol *f, t_fract_param *par);
int				key_press(int key, void *param);
void			draw_fractal(t_cl_str *cl_params, t_fractol *f,
				t_fract_param *par, t_coord *coord);
int				prepare_cl(t_cl_str *params);
t_fract_param	*param_init(void);
t_coord			*init_coord(void);
int				mouse_release(int key, int x, int y, void *param);
int				chill(int key);
void			swap_fractal(int key, t_fract_param *f);
void			reset(int key, t_fract_param *f);
#endif
