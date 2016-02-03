/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 16:37:07 by fnieto            #+#    #+#             */
/*   Updated: 2016/02/03 18:23:34 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map		map(t_vec4 dims)
{
	t_map new;

	new.buf = buffer(dims.x, dims.y, sizeof(t_vertex));
	new.height = vec2(dims.y, dims.z);
	new.cur = 0;
	return (new);
}

t_vertex	get_vertex(t_map map, size_t x, size_t y)
{
	return (((t_vertex*)(map.buf->buf))[map.buf->w * y + x]);
}

void		set_vertex(t_map map, size_t x, size_t y, t_vertex v)
{
	((t_vertex*)(map.buf->buf))[map.buf->w * y + x] = v;
}
