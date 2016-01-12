/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 12:36:19 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/12 12:45:39 by fnieto           ###   ########.fr       */
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

int			plasma_shader(t_shader_info i)
{
	t_vec2 p = add_vec2_1(mul_vec2_1(div_vec2(i.i_frag_coord, i.i_resolution), 2), -1);

	t_float x = p.x;
	t_float y = p.y;
	t_float mov0 = x+y+cos(sin(i.i_global_time)*2.0)*100.+sin(x/100.)*1000.;
	t_float mov1 = y / 0.9 +  i.i_global_time;
	t_float mov2 = x / 0.2;
	t_float c1 = fabs(sin(mov1+i.i_global_time)/2.+mov2/2.-mov1-mov2+i.i_global_time);
	t_float c2 = fabs(sin(c1+sin(mov0/1000.+i.i_global_time)+sin(y/40.+i.i_global_time)+sin((x+y)/100.)*3.));
	t_float c3 = fabs(sin(c2+cos(mov1+mov2+c2)+cos(mov2)+sin(x/1000.)));
	return (encode(c1, c2, c3));
}

int			circle_shader(t_shader_info i)
{
	t_vec2 p = div_vec2_1(sub_vec2(mul_vec2_1(i.i_frag_coord, 2), i.i_resolution), i.i_resolution.y);
	t_float tau = PI*2.0;
	t_float a = atan2(p.x,p.y);
	t_float r = len_vec2(p)*0.75;
	t_vec2 uv = vec2(a/tau,r);
	t_float xCol = (uv.x - (i.i_global_time / 3.0)) * 3.0;
	xCol = MOD(xCol, 3.0);
	t_vec3 horColour = vec3(0.25, 0.25, 0.25);

	if (xCol < 1.0) {

		horColour.x += 1.0 - xCol;
		horColour.y += xCol;
	}
	else if (xCol < 2.0) {

		xCol -= 1.0;
		horColour.y += 1.0 - xCol;
		horColour.z += xCol;
	}
	else {

		xCol -= 2.0;
		horColour.z += 1.0 - xCol;
		horColour.x += xCol;
	}
	uv.x = (2.0 * uv.x) - 1.0;
	uv.y = (2.0 * uv.y) - 1.0;
	t_float beamWidth = (0.7+0.5*cos(uv.x*10.0*tau*0.15*CLAMP(FLOOR(5.0 + 10.0*cos(i.i_global_time)), 0.0, 10.0))) * fabs(1.0 / (30.0 * uv.y));
	t_vec3 horBeam = vec3_1(beamWidth);
	return (encode_vec3(mul_vec3(horBeam, horColour)));
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
		draw_line(a, b, &circle_shader, g_instance->frame);
	}
//	a = vertex(vec3(0, g_instance->frame->h / 2., 0), def);
//	b = vertex(vec3(g_params.res.x, MOD(g_global_time * 60, g_instance->frame->h), 0), def);
//	draw_line(a, b, &uv_shader, g_instance->frame);

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
	g_instance->frame->clear_undrawn = 1;
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
