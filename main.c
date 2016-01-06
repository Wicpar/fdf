/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 12:36:19 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/06 19:20:53 by fnieto           ###   ########.fr       */
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

int			loop(void *param)
{
	int			x;
	int			y;
	t_params	*params;
	int			frame;
	
	params = (t_params*)param;
	frame = params->frame;
	y = -1;
	while (++y < params->window.w)
	{
		x = -1;
		while (++x < params->window.z)
		{
			params->window.x = x;
			params->window.y = y;
			mlx_pixel_put(g_mlx_core, g_mlx_window_main, x, y, frame);
		}
	}
	++params->frame;
	return ((int)param);
}

int			key_event(int keycode, void *param)
{
	if (keycode == 53)
		exit(0);
	ft_putendl(ft_itoa(keycode));
	return ((int)param);
}

t_params	make_params(int ac, char **av)
{
	t_params	params;
	int			i;

	params.window = vec_new(0, 0, 400, 400);
	params.frame = 0;
	params.file = 0;
	i = 0;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-res"))
		{
			params.window.z = (t_float)ft_atoi(av[++i]);
			params.window.w = (t_float)ft_atoi(av[++i]);
		} else
			params.file = av[i];
	}
	return (params);
}

int			main(int ac, char **av)
{
	t_params	params;

	params = make_params(ac, av);
	if (!params.file)
		puterr(0, ft_strjoin(ft_strjoin("usage: ", av[0]), " [-res <x> <y>] <filename>"));
	g_mlx_core = mlx_init();
	if (!g_mlx_core)
		puterr(1, "Failed to load MLX core /!\\");
	g_mlx_window_main = mlx_new_window(g_mlx_core, params.window.z, params.window.w, "fdf");
	if (!g_mlx_window_main)
		puterr(1, "Failed to create main window /!\\");
	mlx_loop_hook(g_mlx_core, &loop, &params);
	mlx_key_hook(g_mlx_window_main, &key_event, &params);
	mlx_loop(g_mlx_core);
}
