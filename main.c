/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 12:36:19 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/07 13:07:51 by fnieto           ###   ########.fr       */
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

int			simple_shader(t_vertex_param params)
{
	return (params.lerp.color);
}

int			loop(void *param)
{
	t_vertex	a;
	t_vertex	b;

	a.pos = vec_new(0, g_params.frame % (int)g_params.window.w, 0, 0);
	a.color = 0x00FFFFFF;
	b.pos = vec_new(g_params.window.z, g_params.frame % (int)g_params.window.w, 0, 0);
	b.color = 0x00000000;
	draw_line(&simple_shader, a, b);
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
	g_params.vertices = strbuff_to_vertbuff(file_to_strbuff(g_params.file));
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
