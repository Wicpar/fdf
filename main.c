/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 12:36:19 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/08 14:03:01 by fnieto           ###   ########.fr       */
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
t_params	g_params;
t_mat		g_camera;

int			uv_shader(t_vertex_param params)
{
	t_vec	uv = vec_new(params.lerp.pos.x / params.params.window.z,params.lerp.pos.y / params.params.window.w , (cos(params.params.frame / 16.) + 1) / 2, 0);
	return (col_fromrgba(uv));
}

int			simple_shader(t_vertex_param params)
{
	t_float time = params.params.frame / 24.;
	t_vec p = vec_new((2.0 * params.lerp.pos.x - params.params.window.z) / params.params.window.w,(2.0 * params.lerp.pos.y - params.params.window.w) / params.params.window.w, 0, 0);
	t_float tau = PI * 2;
	t_float a = atan(p.x/p.y) * 2;
	t_float r = sqrt(vec_lensq(p))*0.75;
	t_vec uv = vec_new(a/tau,r, 0, 0);
	t_float xCol = (uv.x - (time / 3.0)) * 3.0;
	xCol = MOD(xCol, 3.0);
	t_vec horColour = vec_new(0.25, 0.25, 0.25, 0);

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
	t_float beamWidth = (0.7+0.5*cos(uv.x*10.0*tau*0.15*CLAMP(FLOOR(5.0 + 10.0*cos(time)), 0.0, 10.0))) * ABS(1.0 / (30.0 * uv.y));
	t_vec horBeam = vec_new(beamWidth, beamWidth, beamWidth, 0);
	return (col_fromrgba(vec_mul(horBeam, horColour)));
}

int			loop(void *param)
{
	t_vertex	a;
	t_vertex	b;
	size_t		i;

	i = -1;
	while (++i < g_params.window.w)
	{
	a.pos = vec_new(0, (t_float)i, 0, 0);
	a.color = 0x00FFFFFF;
	b.pos = vec_new(g_params.window.z, (t_float)i, 0, 0);
	b.color = 0x00FF00FF;
	draw_line(&simple_shader, a, b);
	}
	g_params.frame += 1;
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

	g_params.window = vec_new(0, 0, 400, 400);
	g_params.frame = 0;
	g_params.file = 0;
	i = 0;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-res"))
		{
			g_params.window.z = (t_float)ft_atoi(av[++i]);
			g_params.window.w = (t_float)ft_atoi(av[++i]);
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
	if (!g_mlx_core)
		puterr(1, "Failed to load MLX core /!\\");
	g_mlx_window_main = mlx_new_window(g_mlx_core, g_params.window.z, g_params.window.w, "fdf");
	if (!g_mlx_window_main)
		puterr(1, "Failed to create main window /!\\");
	mlx_loop_hook(g_mlx_core, &loop, 0);
	mlx_key_hook(g_mlx_window_main, &key_event, 0);
	g_camera = mat_identity();
	mlx_loop(g_mlx_core);
}
