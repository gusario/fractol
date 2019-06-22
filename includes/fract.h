#ifndef FRACT_H

# define FRACT_H

# define WIDTH 1080
# define HEIGHT 1080

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include <inttypes.h>
#include "../libft/libft.h"

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

typedef struct s_coord
{
     double zr;
     double zi;
     double cr;
     double ci;
     double tmp;
}   t_coord;

typedef struct  s_fractol
{
    void *mlx;
    void *win;
    void *img;
    intmax_t x;
    intmax_t y;
    intmax_t z;
    int option_x;
    int option_y;
    int mouse_stop;
    int color_val;
    unsigned int color_max;
    char *data_addr;
    void (*fractal)(struct s_fractol *f);
    int size_line;
    int bpp;
    int endian;
    int zoom_auto;
    double zoom;
    int psycho;
    int i_max;
    double max_imag;
     double min_imag;
     double max_real;
     double min_real;
    t_coord *mdb;
    t_coord *jul;
    t_coord *ship;
    t_coord *newton;
}       t_fractol;


void terminate(char *s);
t_fractol *fract_init();
void julia(t_fractol *f);
void put_pxl(t_fractol *f, int x, int y, unsigned int color);
unsigned int get_color(t_fractol *f, int a);
void mandelbrot(t_fractol *f);
void burningship(t_fractol *f);
int	close_x(void);
int	key_press(int key, t_fractol *f);
int mouse_move(int x, int y, t_fractol *f);
int mouse_zoom(int key, int x, int y, t_fractol *f);
#endif