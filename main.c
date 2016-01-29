/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 12:36:19 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/29 18:16:00 by fnieto           ###   ########.fr       */
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
	return (encode(i.i_vertex_attribs[0].value.v3.z, 1, 1));
}

int			loop(void *param)
{
	t_buffer	*b = (t_buffer*)param;
	t_vertex	*cur;
	size_t		x;
	size_t		y;

	ft_putendl("b");
	gl_begin(GL_LINES, &heightmap, get_instance()->frame);
	ft_putendl("yo");
	y = -1;
	while (++y < b->h)
	{
		x = -1;
		while (++x < b->w - 1)
		{
			cur = &(((t_vertex*)(b->buf))[y * b->w + x]);
			gl_param((t_type)cur->pos, VEC3, 0);
			gl_param(cur->attributes[0].value,
				cur->attributes[0].interpolation, 1);
			gl_vertex(cur->pos);
			//printf("%f, %f, %f\n", cur->pos.x, cur->pos.y, cur->pos.z);
			cur = &(((t_vertex*)(b->buf))[y * b->w + x + 1]);
			gl_param((t_type)cur->pos, VEC3, 0);
			gl_param(cur->attributes[0].value,
				cur->attributes[0].interpolation, 1);
			gl_vertex(cur->pos);
		}
	}
	x = -1;
	while (++x < b->w)
	{
		y = -1;
		while (++y < b->h - 1)
		{
			cur = &(((t_vertex*)(b->buf))[y * b->w + x]);
			gl_param((t_type)cur->pos, VEC3, 0);
			gl_param(cur->attributes[0].value,
				cur->attributes[0].interpolation, 1);
			gl_vertex(cur->pos);
			//printf("%f, %f, %f\n", cur->pos.x, cur->pos.y, cur->pos.z);
			cur = &(((t_vertex*)(b->buf))[(y + 1) * b->w + x]);
			gl_param((t_type)cur->pos, VEC3, 0);
			gl_param(cur->attributes[0].value,
				cur->attributes[0].interpolation, 1);
			gl_vertex(cur->pos);
		}
	}
	//gl_vertex(vec3(0, 0, 0));
	//gl_vertex(vec3(100, 100, 100));
	ft_putendl("z");
	gl_end();
	ft_putendl("a");
	set_time(get_time() + 0.1);
	frame_print(get_instance()->frame);
	mlx_put_image_to_window(g_mlx_core, g_mlx_window_main, g_mlx_frame, 0, 0);
	return ((int)(param = 0));
}

int			key_event(int keycode, void *param)
{
	static t_vec3	trans = {0, 0, 0};
	static t_vec3	angls = {0, -PI, 0};
	static t_float	zoom = 1.5;

	if (keycode == 53)
		exit(0);
	if (keycode == 124 || keycode == 123)
		trans.x += (keycode == 124 ? 1 : -1) * .01;
	if (keycode == 126 || keycode == 125)
		trans.z += (keycode == 126 ? 1 : -1) * .1;
	if (keycode == 24 || keycode == 27)
		zoom *= (keycode == 24 ? 1.01 : .99);
	if (keycode == 2 || keycode == 0)
		angls.y -= (keycode - 1) * PI * 0.05;
	if (keycode == 12 || keycode == 14)
		angls.z -= (keycode - 13) * PI * 0.05;
	if (keycode == 1 || keycode == 13)
		angls.x += (keycode == 1 ? -1 : 1) * PI * 0.05;
	if (keycode == 115 || keycode == 119)
		trans.z += (keycode == 115 ? 1 : -1) * 0.01;
	gl_matrix_mode(GL_MODELVIEW);
	gl_popmatrix();
	gl_popmatrix();
	gl_popmatrix();
	//gl_popmatrix();
	//gl_popmatrix();
	//gl_popmatrix();
	//gl_pushmatrix(mat4_scale(vec3(zoom, zoom, zoom)));
	//gl_pushmatrix(mat4_scale(vec3(0.1, 0.1, 0.1)));
	//gl_pushmatrix(mat4_translation(vec3(g_params.res.x / 2., g_params.res.y / 2., 0)));
	gl_pushmatrix(mul_mat4(mul_mat4(mat4_rotation(vec3(1, 0, 0), angls.x), mat4_rotation(vec3(0, 1, 0), angls.y)), mat4_rotation(vec3(0, 0, 1), angls.z)));
	//gl_pushmatrix(mat4_translation(vec3(g_params.res.x / -2., g_params.res.y / -2., 0)));
	gl_pushmatrix(mat4_translation(vec3(trans.x, trans.y, trans.z)));
	//gl_matrix_mode(GL_PROJECTION);
	//gl_popmatrix();
	gl_pushmatrix(cam_perspective(g_params.res.x / g_params.res.y, PI / 2 * zoom, 1, 1000));
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
	t_buffer	*test;

	make_params(ac, av);
	if (!g_params.file)
		puterr(0, ft_strjoin(ft_strjoin("usage: ", av[0]), " [-res <x> <y>] <filename>"));
	g_mlx_core = mlx_init();
	fred_gl_init(g_params.res.x, g_params.res.y, &draw_frame);
	get_instance()->frame->clear_undrawn = 1;
	if (!g_mlx_core)
		puterr(1, "Failed to load MLX core /!\\");
	g_mlx_window_main = mlx_new_window(g_mlx_core, g_params.res.x, g_params.res.y, "fdf");
	if (!g_mlx_window_main)
		puterr(1, "Failed to create main window /!\\");
	g_mlx_frame = mlx_new_image(g_mlx_core, g_params.res.x, g_params.res.y);
	free(get_instance()->frame->img->buf);
	get_instance()->frame->img->buf = mlx_get_data_addr(g_mlx_frame, &tmp, &tmp, &tmp);
	test = map_to_vert_buff(get_map_data(g_params.file));
	mlx_loop_hook(g_mlx_core, &loop, (void*)test);
	mlx_key_hook(g_mlx_window_main, &key_event, 0);
	//gl_matrix_mode(GL_PROJECTION);
	//gl_pushmatrix(cam_ortho(vec2(0, g_params.res.x), vec2(0, g_params.res.y), vec2(10000, -10000)));
	ft_putendl("preload");
	key_event(-1, 0);
	ft_putendl("postload");
	mlx_do_key_autorepeaton(g_mlx_core);
	mlx_loop(g_mlx_core);
	return (0);
}
