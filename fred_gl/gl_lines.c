/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_lines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 15:28:42 by fnieto            #+#    #+#             */
/*   Updated: 2016/02/01 19:04:25 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"
#include "libft.h"



#include <stdio.h>

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
		//printf("%zu\n", i);
	}
}

void		draw_line(t_vertex a, t_vertex b, t_shader shader, t_frame *f)
{
	size_t		max;
	size_t		i;
	t_vertex	tmp;

	max = MAX(SIZE(CLAMP(LEN(b.pos.x, a.pos.x), -1, 1), (t_float)f->w),
			SIZE(CLAMP(LEN(b.pos.y, a.pos.y), -1, 1), (t_float)f->h));
	i = -1;
	while (++i <= max)
	{
		tmp = vert_lerp(a, b, i, max);
		//printf("%zu, %zu\n%f, %f, %f\n", max , i, tmp.pos.x, tmp.pos.y, tmp.pos.z);
		//printf("2\n%f, %f, %f\n", tmp.pos.x, tmp.pos.y, tmp.pos.z);
		frame_put_pixel(f, tmp, shader);
	}
}
