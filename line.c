/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 09:10:38 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/07 10:39:57 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

void	draw_line(int (*shader)(t_vertex_param), t_vertex a, t_vertex b)
{
	int				i[2];
	t_vertex_param	param;
	t_vec			v[3];
	int				sign[2];
	t_float			alpha;

	i[0] = -1;
	param.params = g_params;
	v[0] = matvec_mul(g_camera, a.pos);
	v[1] = matvec_mul(g_camera, b.pos);
	v[2] = vec_sub(v[1], v[0]);
	i[1] = ABS(MAX(FLOOR(v[2].x), FLOOR(v[2].y)));
	sign[0] = SIGN(v[2].x);
	sign[1] = SIGN(v[2].y);
	while (++i[0] <= i[1])
	{
		alpha = (t_float)i[0] / i[1];
		param.worldpos = col_lerprgba(a.pos, b.pos, alpha);
		param.lerp.pos = col_lerprgba(v[0], v[1], alpha);
		param.lerp.color = col_lerp(a.color, b.color, alpha);
		mlx_pixel_put(g_mlx_core, g_mlx_window_main, FLOOR(param.lerp.pos.x),
				FLOOR(param.lerp.pos.y), shader(param));
	}
}
