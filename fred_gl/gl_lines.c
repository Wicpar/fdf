/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_lines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 15:28:42 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/11 18:47:22 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"
#include "libft.h"

void		gl_lines(t_vertex **verts, size_t **ind, t_shader shader, t_frame *f)
{
	t_vertex	tmp[2];
	size_t		tmpi[2];
	size_t		i;

	i = -1;
	if (ind)
	{
		while (ind[++i])
		{
			tmpi[i % 2] = *ind[i];
			if (i % 2 == 1)
				draw_line(*(verts[tmpi[0]]), *(verts[tmpi[1]]), shader, f);
		}
	}
	else
	{
		while (verts[++i] != 0)
		{
			tmp[i % 2] = *(verts[i]);
			if (i % 2 == 1)
				draw_line(tmp[0], tmp[1], shader, f);
		}
	}
}

void		draw_line(t_vertex a, t_vertex b, t_shader shader, t_frame *f)
{
	size_t		max;
	size_t		i;
	t_vertex	tmp;

	max = MAX(b.pos.x - a.pos.x, b.pos.y - a.pos.y);
	i = -1;
	while (++i <= max)
	{
		tmp = vert_lerp(a, b, i, max);
		frame_put_pixel(f, tmp, shader);
	}
}
