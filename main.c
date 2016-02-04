/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 12:36:19 by fnieto            #+#    #+#             */
/*   Updated: 2016/02/04 18:37:58 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"
#include <stdlib.h>

#include <stdio.h>
#include <math.h>

void		*g_mlx_core;
void		*g_mlx_window_main;
void		*g_mlx_frame;
t_param		g_params;

int			draw_px(int x, int y, int color)
{
	return (mlx_pixel_put(g_mlx_core, g_mlx_window_main, x, y, color));
}

int			draw_frame(int x, int y, int color)
{
	return (x + y + color);
}

int			white(t_shader_info i)
{
	i = *(&i);
	return (0xFFFFFF);
}

int			heightmap(t_shader_info i)
{
	//ft_print_memory(&(i.i_vertex_attribs[0]), sizeof (t_attrib));
	//ft_putendl("<-->");
	//ft_print_memory(&(i.i_vertex_attribs[0].value.v3.z), sizeof(t_float));
	//if (i.i_vertex_attribs[0].value.v3.z != 0)
	//printf("%f\n",i.i_vertex_attribs[0].value.v3.z);
	//t_vec3 pos = i.i_vertex_attribs[0].value.v3;
	//printf("%e, %e, %e\n", pos.x, pos.y, pos.z);
	//ft_putendl("");
	return (encode_vec3(vec3_1(i.i_vertex_attribs[0].value.v3.z / 20 + 0.5)));
}

int			loop(void *param)
{
	t_map		*b = ((t_map*)param);
	t_vertex	*cur;
	size_t		x;
	size_t		y;

	if (b->cur == 0)
	{
		gl_begin(GL_LINES, &funky_sphere_shader, get_instance()->frame);
		y = -1;
		while (++y < b->buf->h)
		{
			x = -1;
			while (++x < b->buf->w - 1)
			{
				cur = &(((t_vertex*)(b->buf->buf))[y * b->buf->w + x]);
				gl_param(T(cur->pos), VEC3, 0);
				gl_param(cur->attributes[0].value,
						cur->attributes[0].interpolation, 1);
				gl_param((t_type)b->height, VEC2, 2);
				gl_vertex(cur->pos);
				printf("%zu %zu:%e, %e, %e\n", x, y, cur->pos.x, cur->pos.y, cur->pos.z);
				cur = &(((t_vertex*)(b->buf->buf))[y * b->buf->w + x + 1]);
				gl_param((t_type)cur->pos, VEC3, 0);
				gl_param(cur->attributes[0].value,
						cur->attributes[0].interpolation, 1);
				gl_param((t_type)b->height, VEC2, 2);
				gl_vertex(cur->pos);
			}
		}
		x = -1;
		while (++x < b->buf->w)
		{
			y = -1;
			while (++y < b->buf->h - 1)
			{
				cur = &(((t_vertex*)(b->buf->buf))[y * b->buf->w + x]);
				gl_param((t_type)cur->pos, VEC3, 0);
				gl_param(cur->attributes[0].value,
						cur->attributes[0].interpolation, 1);
				gl_param((t_type)b->height, VEC2, 2);
				gl_vertex(cur->pos);
				printf("%zu %zu:%e, %e, %e\n", x, y, cur->pos.x, cur->pos.y, cur->pos.z);
				cur = &(((t_vertex*)(b->buf->buf))[(y + 1) * b->buf->w + x]);
				gl_param((t_type)cur->pos, VEC3, 0);
				gl_param(cur->attributes[0].value,
						cur->attributes[0].interpolation, 1);
				gl_param((t_type)b->height, VEC2, 2);
				gl_vertex(cur->pos);
			}
		}
		b->cur = gl_end();
	}
	gl_draw_buf(b->cur, &funky_height_shader, get_instance()->frame, GL_LINES);
	set_time(get_time() + 0.1);
	frame_print(get_instance()->frame);
	mlx_put_image_to_window(g_mlx_core, g_mlx_window_main, g_mlx_frame, 0, 0);
	return ((int)(param = 0));
}

int			key_event(int keycode, void *param)
{
	static t_vec3	trans = {0, 0, 100};
	static t_vec3	angls = {0, -PI, -PI};
	static t_float	h = 0.5;
	static t_float	zoom = 1;

	if (keycode == 53)
		exit(0);
	if (keycode == 126 || keycode == 125)
		h *= (keycode == 126 ? 1.1 : 0.9);
	if (keycode == 24 || keycode == 27)
		zoom *= (keycode == 24 ? 1.01 : .99);
	if (keycode == 2 || keycode == 0)
		angls.y += (keycode - 1) * PI * 0.05;
	if (keycode == 12 || keycode == 14)
		angls.z -= (keycode - 13) * PI * 0.05;
	if (keycode == 1 || keycode == 13)
		angls.x += (keycode == 1 ? -1 : 1) * PI * 0.05;
	gl_matrix_mode(GL_MODELVIEW);
	gl_popmatrix();
	gl_popmatrix();
	gl_popmatrix();
	gl_popmatrix();
	gl_pushmatrix(mat4_scale(vec3(1, 1, h)));
	gl_pushmatrix(mat4_rotation(angls.x, angls.y, angls.z));
	gl_pushmatrix(mat4_translation(vec3(trans.x, trans.y, trans.z)));
	gl_pushmatrix(cam_perspective(g_params.res.x / g_params.res.y, PI / 4 * zoom, 0.1, 10000));
	ft_putendl(ft_itoa(keycode));
	return ((int)(param = 0));
}

void		make_params(int ac, char **av)
{
	int			i;

	g_params.res = vec2(400, 400);
	g_params.file = 0;
	i = 0;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-res"))

		{
			g_params.res.x = (t_float)ft_atoi(av[++i]);
			g_params.res.y = (t_float)ft_atoi(av[++i]);
		} else
			g_params.file = av[i];
	}
}

int			main(int ac, char **av)
{
	int			tmp;
	t_map		test;

	make_params(ac, av);
	if (!g_params.file)
		puterr(0, ft_strjoin(ft_strjoin("usage: ", av[0]), " [-res <x> <y>] <filename>"));
	g_mlx_core = mlx_init();
	fred_gl_init(g_params.res.x, g_params.res.y, &draw_frame);
	get_instance()->frame->clear_undrawn = 1;
	get_instance()->frame->depth_func = 1;
	if (!g_mlx_core)
		puterr(1, "Failed to load MLX core /!\\");
	g_mlx_window_main = mlx_new_window(g_mlx_core, g_params.res.x, g_params.res.y, "fdf");
	if (!g_mlx_window_main)
		puterr(1, "Failed to create main window /!\\");
	g_mlx_frame = mlx_new_image(g_mlx_core, g_params.res.x, g_params.res.y);
	free(get_instance()->frame->img->buf);
	get_instance()->frame->img->buf = mlx_get_data_addr(g_mlx_frame, &tmp, &tmp, &tmp);
	test = map_to_vert_buff(get_map_data(g_params.file));
	mlx_loop_hook(g_mlx_core, &loop, (void*)(&test));
	mlx_hook(g_mlx_window_main,2, 4, &key_event, (void*)(&test));
	key_event(-1, 0);
	mlx_loop(g_mlx_core);
	return (0);
}
