/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_lines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 15:28:42 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/14 13:45:43 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"
#include "libft.h"

void		gl_lines(t_list *verts, t_list *ind, t_shader shader, t_frame *f)
{
	t_vertex	tmp[2];
	size_t		tmpi[2];
	size_t		i;

	i = -1;
	if (ind)
	{
		while (ind)
		{
			tmpi[i % 2] = *((size_t*)(ind->content));
			if (i % 2 == 1)
				draw_line(*(verts[tmpi[0]]), *(verts[tmpi[1]]), shader, f);
			ind = ind->next;
		}
	}
	else
	{
		while (verts)
		{
			tmp[i % 2] = *(verts[i]);
			if (i % 2 == 1)
				draw_line(tmp[0], tmp[1], shader, f);
			verts = verts->next;
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
