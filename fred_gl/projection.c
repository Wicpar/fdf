/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 14:04:51 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/28 19:52:35 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"
#include <math.h>

t_mat4		cam_ortho(t_vec2 lr, t_vec2 tb, t_vec2 nf)
{
	t_mat4	new;

	new = mat4_identity();
	new.m00 = 2. / (lr.y - lr.x);
	new.m11 = 2. / (tb.x - tb.y);
	new.m22 = -2. / (nf.y - nf.x);
	new.m30 = -(lr.y + lr.x) / (lr.y - lr.x);
	new.m31 = -(tb.x + tb.y) / (tb.x - tb.y);
	new.m32 = -(nf.y + nf.x) / (nf.y - nf.x);
	return (new);
}

t_mat4		cam_perspective(t_float aspect, t_float fovy, t_vec2 nf)
{
	t_float t;

	t = tan(fovy/2.);
	return (mat4(
		vec4(1. / (aspect * t), 0, 0, 0),
		vec4(0, 1. / t, 0, 0),
		vec4(0, 0, (-nf.x + nf.y) / (nf.x - nf.y),
		(2 * nf.x * nf.y) / (nf.x - nf.y)),
		vec4(0, 0, 1, 0)
		));
}
