/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weird_shit4cl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 17:03:31 by srobert-          #+#    #+#             */
/*   Updated: 2019/06/28 07:53:30 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

void	draw_fractal(t_cl_str *cl_params, t_fractol *f, t_fract_param *par,
		t_coord *coord)
{
	cl_mem	memobj;
	int		ret;
	size_t	global_work_size[2];

	global_work_size[0] = WIDTH;
	global_work_size[1] = HEIGHT;
	memobj = clCreateBuffer(cl_params->context, CL_MEM_READ_WRITE,
							WIDTH * HEIGHT * 4, NULL, &ret);
	ret = clSetKernelArg(cl_params->kernel, 0, sizeof(int *), &memobj);
	ret = clSetKernelArg(cl_params->kernel, 1, sizeof(t_fract_param), par);
	ret = clSetKernelArg(cl_params->kernel, 2, sizeof(t_fract_param), coord);
	ret = clEnqueueNDRangeKernel(cl_params->queue, cl_params->kernel, 2, NULL,
								global_work_size, NULL, 0, NULL, NULL);
	ret = clEnqueueReadBuffer(cl_params->queue, memobj, CL_FALSE, 0,
							WIDTH * HEIGHT * 4, f->data_addr, 0, NULL, NULL);
	clFinish(cl_params->queue);
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
	text(f, par);
}

int		prepare_cl(t_cl_str *params)
{
	t_cl_prep prep;

	prep.ret = clGetPlatformIDs(1, &(prep.platf), &(prep.num_platforms));
	prep.ret = clGetDeviceIDs(prep.platf, CL_DEVICE_TYPE_DEFAULT, 1,
							&(params->device), &(prep.dev));
	(params->context) = clCreateContext(NULL, 1, &(params->device),
										NULL, NULL, &(prep.ret));
	(params->queue) = clCreateCommandQueue(params->context, params->device,
											0, &(prep.ret));
	prep.filename = "./srcs/fractals.cl";
	prep.fp = fopen(prep.filename, "r");
	prep.source_str = (char *)malloc(50000);
	prep.source_size = fread(prep.source_str, 1, 50000, prep.fp);
	fclose(prep.fp);
	prep.program = clCreateProgramWithSource(params->context, 1,
	(const char **)&(prep.source_str), (const size_t *)&(prep.source_size),
	&(prep.ret));
	prep.ret = clBuildProgram(prep.program, 1, &(params->device),
								NULL, NULL, NULL);
	params->kernel = clCreateKernel(prep.program, "fractal", &(prep.ret));
	free(prep.source_str);
	return (1);
}
