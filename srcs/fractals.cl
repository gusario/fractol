
struct RGB
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

struct HSV
{
    double H;
    double S;
    double V;
};

typedef struct s_point
{
    double x;
    double y;
    double z;
    int color;
} t_point;

typedef struct s_coord
{
    double zr;
    double zi;
    double cr;
    double ci;
    double tmp;
} t_coord;

typedef struct s_fract_param
{
    double max_imag;
    double min_imag;
    double max_real;
    double min_real;
    int i_max;
    int name;
    int color_val;
    unsigned int color_max;
    int height;
    int width;
    int color_palete;
    int multi_power;
} t_fract_param;

struct RGB HSVToRGB(struct HSV hsv)
{
    double r = 0, g = 0, b = 0;

    if (hsv.S == 0)
    {
        r = hsv.V;
        g = hsv.V;
        b = hsv.V;
    }
    else
    {
        int i;
        double f, p, q, t;

        if (hsv.H == 360)
            hsv.H = 0;
        else
            hsv.H = hsv.H / 60;

        i = (int)trunc(hsv.H);
        f = hsv.H - i;

        p = hsv.V * (1.0 - hsv.S);
        q = hsv.V * (1.0 - (hsv.S * f));
        t = hsv.V * (1.0 - (hsv.S * (1.0 - f)));

        switch (i)
        {
        case 0:
            r = hsv.V;
            g = t;
            b = p;
            break;

        case 1:
            r = q;
            g = hsv.V;
            b = p;
            break;

        case 2:
            r = p;
            g = hsv.V;
            b = t;
            break;

        case 3:
            r = p;
            g = q;
            b = hsv.V;
            break;

        case 4:
            r = t;
            g = p;
            b = hsv.V;
            break;

        default:
            r = hsv.V;
            g = p;
            b = q;
            break;
        }
    }

    struct RGB rgb;
    rgb.R = r * 255;
    rgb.G = g * 255;
    rgb.B = b * 255;

    return rgb;
}

int get_color(t_fract_param *f, int iter, double rng)
{
    struct HSV col;
    struct RGB ret_col;
    unsigned int c;

    if (iter == f->i_max)
        return (f->color_max);
    if (f->color_palete == 1)
    {
        iter = iter + 1 - log(log(rng));
        col.H = (180 * ((double)iter) + f->color_val) / f->i_max;
        col.S = 1;
        col.V = 1;
        ret_col = HSVToRGB(col);
    }
    else
    {
        ret_col.R = (unsigned char)(sin(0.016 * iter + 4) * 230 + 25) * f->color_val;
        ret_col.G = (unsigned char)(sin(0.013 * iter + 2) * 230 + 25) * f->color_val;
        ret_col.B = (unsigned char)(sin(0.01 * iter + 1) * 230 + 25) * f->color_val;
    }
    c = (ret_col.R << 16) + (ret_col.G << 8) + ret_col.B;
    return (c);
}

void mandelbrot(__global int *res, t_fract_param *f)
{
    int x;
    int y;
    double step_i;
    double step_r;
    t_coord mdb;
    int i;

    step_i = (f->max_imag - f->min_imag) / f->height;
    step_r = (f->max_real - f->min_real) / f->width;
    x = get_global_id(0);
    y = get_global_id(1);
    mdb.zi = 0;
    mdb.zr = 0;
    mdb.ci = f->max_imag - step_i * y;
    mdb.cr = f->min_real + step_r * x;
    i = -1;
    while (++i < f->i_max)
    {
        mdb.tmp = mdb.zr;
        mdb.zr = mdb.zr * mdb.zr - mdb.zi * mdb.zi + mdb.cr;
        mdb.zi = 2 * mdb.tmp * mdb.zi + mdb.ci;
        if (mdb.zr * mdb.zr + mdb.zi * mdb.zi > 4)
            break;
    }
    res[f->width * (f->height - y) + x] = get_color(f, i, mdb.zr * mdb.zr + mdb.zi * mdb.zi);
}

void multibrot(__global int *res, t_fract_param *f)
{
    int x;
    int y;
    double step_i;
    double step_r;
    t_coord mdb;
    int i;

    step_i = (f->max_imag - f->min_imag) / f->height;
    step_r = (f->max_real - f->min_real) / f->width;
    x = get_global_id(0);
    y = get_global_id(1);
    mdb.zi = 0;
    mdb.zr = 0;
    mdb.ci = f->max_imag - step_i * y;
    mdb.cr = f->min_real + step_r * x;
    i = -1;
    while (++i < f->i_max)
    {
        mdb.tmp = pow(mdb.zr * mdb.zr + mdb.zi * mdb.zi, f->multi_power / 2) * cos(f->multi_power * atan2(mdb.zi, mdb.zr)) + mdb.cr;
        mdb.zi = pow(mdb.zr * mdb.zr + mdb.zi * mdb.zi, f->multi_power / 2) * sin(f->multi_power * atan2(mdb.zi, mdb.zr)) + mdb.ci;
        mdb.zr = mdb.tmp;
        if (mdb.zr * mdb.zr + mdb.zi * mdb.zi > 4)
            break;
    }
    res[f->width * (f->height - y) + x] = get_color(f, i, mdb.zr * mdb.zr + mdb.zi * mdb.zi);
}

void julia(__global int *res, t_fract_param *f, t_coord *jul)
{
    int x;
    int y;
    double step_i;
    double step_r;
    int i;

    step_i = (f->max_imag - f->min_imag) / f->height;
    step_r = (f->max_real - f->min_real) / f->width;
    x = get_global_id(0);
    y = get_global_id(1);

    jul->zi = f->max_imag - step_i * y;
    jul->zr = f->min_real + step_r * x;
    i = -1;
    while (++i < f->i_max)
    {
        jul->tmp = jul->zr;
        jul->zr = jul->zr * jul->zr - jul->zi * jul->zi + jul->cr;
        jul->zi = 2 * jul->tmp * jul->zi + jul->ci;
        if (jul->zr * jul->zr + jul->zi * jul->zi > 4)
            break;
    }
    res[f->width * (f->height - y) + x] = get_color(f, i, jul->zr * jul->zr + jul->zi * jul->zi);
}

void multijulia(__global int *res, t_fract_param *f, t_coord *mdb)
{
	int x;
    int y;
    double step_i;
    double step_r;
    int i;

    step_i = (f->max_imag - f->min_imag) / f->height;
    step_r = (f->max_real - f->min_real) / f->width;
    x = get_global_id(0);
    y = get_global_id(1);
    mdb->zi = f->max_imag - step_i * y;
    mdb->zr = f->min_real + step_r * x;
    i = -1;
    while (++i < f->i_max)
    {
        mdb->tmp = pow(mdb->zr * mdb->zr + mdb->zi * mdb->zi, f->multi_power / 2) * cos(f->multi_power * atan2(mdb->zi, mdb->zr)) + mdb->cr;
        mdb->zi = pow(mdb->zr * mdb->zr + mdb->zi * mdb->zi, f->multi_power / 2) * sin(f->multi_power * atan2(mdb->zi, mdb->zr)) + mdb->ci;
        mdb->zr = mdb->tmp;
        if (mdb->zr * mdb->zr + mdb->zi * mdb->zi > 4)
            break;
    }
    res[f->width * (f->height - y) + x] = get_color(f, i, mdb->zr * mdb->zr + mdb->zi * mdb->zi);
}

void antimandel(__global int *res, t_fract_param *f, t_coord *anti)
{
	int x;
    int y;
    double step_i;
    double step_r;
    int i;
	double disk;

    step_i = (f->max_imag - f->min_imag) / f->height;
    step_r = (f->max_real - f->min_real) / f->width;
    x = get_global_id(0);
    y = get_global_id(1);
    anti->zi = f->max_imag - step_i * y;
    anti->zr = f->min_real + step_r * x;
    i = -1;
    while (++i < f->i_max)
    {
		disk = anti->zr * anti->zr * anti->zr * anti->zr + anti->zr * anti->zr * anti->zi * anti->zi + anti->zi * anti->zi * anti->zi * anti->zi;
		if (disk == 0)
			break;
        anti->tmp = (anti->zr * anti->zr - anti->zi * anti->zi) / disk + anti->cr;
		anti->zi = -2 * anti->zr * anti->zi / disk + anti->ci;
		anti->zr = anti->tmp;
        if (anti->zr * anti->zr + anti->zi * anti->zi > 4)
            break;
    }
    res[f->width * (f->height - y) + x] = get_color(f, i, anti->zr * anti->zr + anti->zi * anti->zi);
}

void burningship(__global int *res, t_fract_param *f)
{
    int x;
    int y;
    double step_i;
    double step_r;
    t_coord ship;
    int i;

    step_i = (f->max_imag - f->min_imag) / f->height;
    step_r = (f->max_real - f->min_real) / f->width;
    x = get_global_id(0);
    y = get_global_id(1);
    ship.zi = 0;
    ship.zr = 0;
    ship.ci = f->max_imag - step_i * y;
    ship.cr = f->min_real + step_r * x;
    i = -1;
    while (++i < f->i_max)
    {
        ship.tmp = ship.zr;
        ship.zr = ship.zr * ship.zr - ship.zi * ship.zi + ship.cr;
        ship.zi = 2 * fabs(ship.tmp * ship.zi) + ship.ci;
        if (ship.zr * ship.zr + ship.zi * ship.zi > 4)
            break;
    }

    res[f->width * (f->height - y) + x] = get_color(f, i, ship.zr * ship.zr + ship.zi * ship.zi);
}

void dickship(__global int *res, t_fract_param *f)
{
    int x;
    int y;
    double step_i;
    double step_r;
    t_coord ship;
    int i;

    step_i = (f->max_imag - f->min_imag) / f->height;
    step_r = (f->max_real - f->min_real) / f->width;
    x = get_global_id(0);
    y = get_global_id(1);
    ship.zi = 0;
    ship.zr = 0;
    ship.ci = f->max_imag - step_i * y;
    ship.cr = f->min_real + step_r * x;
    i = -1;
    while (++i < f->i_max)
    {
        ship.tmp = ship.zr;
        ship.zr = ship.zr * ship.zr - ship.zi * ship.zi + ship.cr;
        ship.zi = 2 * fabs(ship.tmp) * ship.zi + ship.ci;
        if (ship.zr * ship.zr + ship.zi * ship.zi > 4)
            break;
    }

    res[f->width * (f->height - y) + x] = get_color(f, i, ship.zr * ship.zr + ship.zi * ship.zi);
}



// void	put_xernya(t_screen scr, int WIN_X, int WIN_Y, __global int *res)
// {
// 	int			x;
// 	int			y;
// 	int			iter;
// 	double		step_i;
// 	double		step_r;
// 	double		res_i;
// 	double		res_r;
// 	double		r;
// 	double		i;
// 	double		dbl_i;
// 	t_point		point;

//     x = get_global_id(0);
//     y = get_global_id(1);
// 	step_i = (scr.max_i - scr.min_i) / WIN_Y;
// 	step_r = (scr.max_r - scr.min_r) / WIN_X;
// 	i = scr.jul_im;
// 	r = scr.jul_re;
// 	res_i = scr.max_i - step_i * y;
// 	res_r = scr.min_r + step_r * x;
// 	point.x = x;
// 	point.y = WIN_Y - y;
// 	iter = -1;
// 	while (++iter < scr.iter)
// 	{
// 		dbl_i = res_i;
// 		res_i = 3 * res_r * res_i * res_r - res_i * res_i * res_i + i;
// 		res_r = res_r * res_r * res_r - 3 * dbl_i * dbl_i * res_r + r - 1;
// 		if (fabs(res_r) > 50 && fabs(res_i) > 2500)
// 			break;
// 	}
// 	point.color = get_color(iter, &scr, res_i * res_i + res_r * res_r);
// 	res[WIN_X * (WIN_Y - y) + x] = point.color;
// }

void biomorph(__global int *res, t_fract_param *f, t_coord *bio)
{
	int x;
    int y;
    double step_i;
    double step_r;
    int i;

    step_i = (f->max_imag - f->min_imag) / f->height;
    step_r = (f->max_real - f->min_real) / f->width;
    x = get_global_id(0);
    y = get_global_id(1);
    bio->zi = f->max_imag - step_i * y;
    bio->zr = f->min_real + step_r * x;
    i = -1;
    while (++i < f->i_max)
    {
		bio->tmp = pow(bio->zr, 3) - 3 * bio->zi * bio->zi * bio->zr + bio->cr - 1;
		bio->zi = 3 * bio->zr * bio->zr * bio->zi - pow(bio->zi, 3) + bio->ci;
		bio->zr = bio->tmp;
        if (fabs(bio->zr) > 50 && fabs(bio->zi) > 2500)
            break;
    }
    res[f->width * (f->height - y) + x] = get_color(f, i, bio->zr * bio->zr + bio->zi * bio->zi);
}

__kernel void fractal(__global int *res, t_fract_param f, t_coord coord)
{
    if (f.name == 1)
        mandelbrot(res, &f);
    else if (f.name == 3)
        burningship(res, &f);
    else if (f.name == 2)
        julia(res, &f, &coord);
    else if (f.name == 4)
        dickship(res, &f);
    else if (f.name == 5)
        multibrot(res, &f);
	else if (f.name == 6)
		multijulia(res, &f, &coord);
	else if (f.name == 7)
		antimandel(res, &f, &coord);
	else if (f.name == 8)
		biomorph(res, &f, &coord);
}