/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 12:36:19 by fnieto            #+#    #+#             */
/*   Updated: 2016/02/04 22:53:18 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"
#include <stdlib.h>
#include <math.h>

int			draw_frame(int x, int y, int color)
{
	return (x + y + color);
}

int			loop(void *param)
{
	t_map		*b;

	b = (t_map*)param;
	if (!b->cur)
		init_verts(b);
	gl_draw_buf(b->cur, &palette_height, get_instance()->frame, GL_LINES);
	set_time(get_time() + 0.1);
	frame_print(get_instance()->frame);
	mlx_put_image_to_window(GV(MLX_CORE).v, GV(MLX_WINDOW).v,
		GV(MLX_FRAME).v, 0, 0);
	return ((int)(param = 0));
}

int			key_event(int keycode, void *param)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 126 || keycode == 125)
		GV(C_HEIGHT).tf *= (keycode == 126 ? 1.1 : 0.9);
	if (keycode == 24 || keycode == 27)
		GV(C_ZOOM).tf *= (keycode == 24 ? 1.01 : .99);
	if (keycode == 2 || keycode == 0)
		GV(C_ANGLS).v3.y += PI * 0.05 * (keycode - 1);
	if (keycode == 12 || keycode == 14)
		GV(C_ANGLS).v3.z -= PI * 0.05 * (keycode - 13);
	if (keycode == 1 || keycode == 13)
		GV(C_ANGLS).v3.x += (keycode == 1 ? -1 : 1) * PI * 0.05;
	gl_matrix_mode(GL_MODELVIEW);
	gl_popmatrix();
	gl_popmatrix();
	gl_popmatrix();
	gl_popmatrix();
	gl_pushmatrix(mat4_scale(vec3(1, 1, GV(C_HEIGHT).tf)));
	gl_pushmatrix(mat4_rotation(GV(C_ANGLS).v3));
	gl_pushmatrix(mat4_translation(GV(C_TRANS).v3));
	gl_pushmatrix(cam_perspective(
		GV(F_RES).v2.x / GV(F_RES).v2.y, PI / 2 * GV(C_ZOOM).tf, 0.1, 10000));
	ft_putendl(ft_itoa(keycode));
	return ((int)(param = 0));
}

void		make_params(int ac, char **av)
{
	int			i;

	SV(F_RES, vec2(400, 400));
	SV(F_FILEPTR, 0);
	i = 0;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-res"))
		{
			GV(F_RES).v2.x = (t_float)ft_atoi(av[++i]);
			GV(F_RES).v2.y = (t_float)ft_atoi(av[++i]);
		}
		else
			SV(F_FILEPTR, (void*)av[i]);
	}
}

int			main(int ac, char **av)
{
	int			tmp;
	t_map		test;

	make_params(ac, av);
	if (!GV(F_FILEPTR).v)
		puterr(0, ft_strjoin(ft_strjoin("usage: ", av[0]),
			" [-res <x> <y>] <filename>"));
	SV(MLX_CORE, mlx_init());
	fred_gl_init(GV(F_RES).v2.x, GV(F_RES).v2.y, &draw_frame);
	get_instance()->frame->clear_undrawn = 1;
	get_instance()->frame->depth_func = 1;
	SV(MLX_WINDOW,
		mlx_new_window(GV(MLX_CORE).v, GV(F_RES).v2.x, GV(F_RES).v2.y, "fdf"));
	SV(MLX_FRAME,
		mlx_new_image(GV(MLX_CORE).v, GV(F_RES).v2.x, GV(F_RES).v2.y));
	free(get_instance()->frame->img->buf);
	get_instance()->frame->img->buf =
		mlx_get_data_addr(GV(MLX_FRAME).v, &tmp, &tmp, &tmp);
	test = map_to_vert_buff(get_map_data((char*)(GV(F_FILEPTR).v)));
	mlx_loop_hook(GV(MLX_CORE).v, &loop, (void*)(&test));
	mlx_hook(GV(MLX_WINDOW).v, 2, 4, &key_event, (void*)(&test));
	init_controls(vec2(test.buf->w, test.buf->h));
	key_event(-1, 0);
	mlx_loop(GV(MLX_CORE).v);
	return (0);
}
