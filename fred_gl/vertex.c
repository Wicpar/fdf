/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 11:39:59 by fnieto            #+#    #+#             */
/*   Updated: 2016/02/02 20:03:56 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"



#include <stdio.h>
t_attrib		attrib_null(void)
{
	static t_attrib		attrib_null = {0, {0}};

	return (attrib_null);
}

t_vertex		vertex(t_vec3 pos, t_attrib attribs[8])
{
	t_vertex	new;
	size_t		i;

	new.pos = pos;
	i = -1;
	while (++i < 8)
	{
		new.attributes[i] = attribs[i];
	}
	return (new);
}

t_attrib		a_lerp
	(t_attrib a, t_attrib b, t_float x, t_float max)
{
	t_attrib	new;

	if (a.interpolation == b.interpolation)
	{
		if (a.interpolation == FLOAT)
			new.value = T(LERP(a.value.tf, b.value.tf, x, max));
		else if (a.interpolation == VEC2)
			new.value = T(lerp_vec2_1(a.value.v2, b.value.v2, x, max));
		else if (a.interpolation == VEC3)
			new.value = T(lerp_vec3_1(a.value.v3, b.value.v3, x, max));
		else if (a.interpolation == VEC4)
			new.value = T(lerp_vec4_1(a.value.v4, b.value.v4, x, max));
		else
			new.value = (x < max / 2. ? a.value : b.value);
		new.interpolation = a.interpolation;
		return (new);
	}
	new.value = (x < max / 2. ? a.value : b.value);
	new.interpolation = NONE;
	return (new);
}

t_vertex		vert_lerp(t_vertex a, t_vertex b, t_float x, t_float max)
{
	t_vertex	new;
	size_t		i;

	new.pos = lerp_vec3_1(a.pos, b.pos, x, max);
	i = -1;
	while (++i < 8)
	{
		new.attributes[i] = a_lerp(a.attributes[i], b.attributes[i], x, max);
	}
	return (new);
}
