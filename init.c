/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 21:17:24 by fnieto            #+#    #+#             */
/*   Updated: 2016/02/04 23:22:53 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		insert_params(t_vertex *cur, t_map *b)
{
	gl_param(T(cur->pos), VEC3, 0);
	gl_param(cur->attributes[0].value, cur->attributes[0].interpolation, 1);
	gl_param((t_type)b->height, VEC2, 2);
}

void		makex(t_map *b)
{
	size_t		x;
	size_t		y;
	t_vertex	*cur;
	t_vertex	*cur2;

	y = -1;
	while (++y < b->buf->h)
	{
		x = -1;
		while (++x < b->buf->w - 1)
		{
			cur = &(((t_vertex*)(b->buf->buf))[y * b->buf->w + x]);
			cur2 = &(((t_vertex*)(b->buf->buf))[y * b->buf->w + x + 1]);
			if (len_vec2(sub_vec2(vec2(cur->pos.x, cur->pos.y),
				vec2(cur2->pos.x, cur2->pos.y))) > 1.1)
				continue ;
			insert_params(cur, b);
			gl_vertex(cur->pos);
			insert_params(cur2, b);
			gl_vertex(cur2->pos);
		}
	}
}

void		makey(t_map *b)
{
	size_t		x;
	size_t		y;
	t_vertex	*cur;
	t_vertex	*cur2;

	x = -1;
	while (++x < b->buf->w)
	{
		y = -1;
		while (++y < b->buf->h - 1)
		{
			cur = &(((t_vertex*)(b->buf->buf))[y * b->buf->w + x]);
			cur2 = &(((t_vertex*)(b->buf->buf))[(y + 1) * b->buf->w + x]);
			if (len_vec2(sub_vec2(vec2(cur->pos.x, cur->pos.y),
				vec2(cur2->pos.x, cur2->pos.y))) > 1.1)
				continue ;
			insert_params(cur, b);
			gl_vertex(cur->pos);
			insert_params(cur2, b);
			gl_vertex(cur2->pos);
		}
	}
}

void		init_verts(t_map *b)
{
	gl_begin(GL_LINES, &funky_sphere_shader, get_instance()->frame);
	makex(b);
	makey(b);
	b->cur = gl_end();
}
