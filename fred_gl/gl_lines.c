/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_lines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 15:28:42 by fnieto            #+#    #+#             */
/*   Updated: 2016/02/04 20:49:03 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"
#include "libft.h"

void		gl_line_strip(t_list *verts, t_shader shader, t_frame *f)
{
	t_vertex	tmp[2];
	size_t		i;

	i = 0;
	while (verts)
	{
		tmp[0] = tmp[1];
		tmp[1] = gl_transform(*((t_vertex*)(verts->content)));
		if (i != 0)
			draw_line(tmp[0], tmp[1], shader, f);
		verts = verts->next;
		++i;
	}
}

void		gl_lines(t_list *verts, t_shader shader, t_frame *f)
{
	t_vertex	tmp[2];
	size_t		i;

	i = 0;
	while (verts)
	{
		tmp[i % 2] = gl_transform(*((t_vertex*)(verts->content)));
		if (i % 2 == 1)
			draw_line(tmp[0], tmp[1], shader, f);
		verts = verts->next;
		++i;
	}
}

void		draw_line(t_vertex a, t_vertex b, t_shader shader, t_frame *f)
{
	int			max;
	int			i;
	t_vertex	tmp;

	max = MAX(SIZE(LEN(b.pos.x, a.pos.x), (t_float)f->w),
			SIZE(LEN(b.pos.y, a.pos.y), (t_float)f->h));
	i = -1;
	while (++i < max)
	{
		tmp = vert_lerp(a, b, i, max);
		frame_put_pixel(f, tmp, shader);
	}
}
