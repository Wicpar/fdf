/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 12:36:19 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/11 19:05:21 by fnieto           ###   ########.fr       */
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
t_param		g_params;
t_mat4		g_camera;

int			uv_shader(t_shader_info params)
{
	int		col;
	t_vec2	uv = div_vec2(params.i_frag_coord, params.i_resolution);
	col = (encode(uv.x, uv.y, FRACT(params.i_global_time)));
	return (col);
}

int			simple_shader(t_shader_info params)
{
	return ((int)params.i_global_time);
}

int			draw_px(int x, int y, int color)
{
	return (mlx_pixel_put(g_mlx_core, g_mlx_window_main, x, y, color));
}

int			loop(void *param)
{
	static t_attrib			def[8];
	t_vertex				a;
	t_vertex				b;
	size_t					i;


	i = -1;
	while (++i < 8)
	{
		def[i] = g_attrib_null;
	}
	i = -1;
	while (++i < g_params.res.y)
	{
		a = vertex(vec3(0, (t_float)i, 0), def);
		b = vertex(vec3(g_params.res.x, (t_float)i, 0), def);
		draw_line(a, b, &uv_shader, g_instance->frame);
	}
	g_global_time += 1. / 60.;
	frame_print(g_instance->frame);
	return ((int)param);
}

int			key_event(int keycode, void *param)
{
	if (keycode == 53)
		exit(0);
	ft_putendl(ft_itoa(keycode));
	return ((int)param);
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
	make_params(ac, av);
	if (!g_params.file)
		puterr(0, ft_strjoin(ft_strjoin("usage: ", av[0]), " [-res <x> <y>] <filename>"));
	g_mlx_core = mlx_init();
	fred_gl_init(g_params.res.x, g_params.res.y, &draw_px);
	if (!g_mlx_core)
		puterr(1, "Failed to load MLX core /!\\");
	g_mlx_window_main = mlx_new_window(g_mlx_core, g_params.res.x, g_params.res.y, "fdf");
	if (!g_mlx_window_main)
		puterr(1, "Failed to create main window /!\\");
	mlx_loop_hook(g_mlx_core, &loop, 0);
	mlx_key_hook(g_mlx_window_main, &key_event, 0);
	g_camera = g_mat4_identity;
	mlx_loop(g_mlx_core);
}
