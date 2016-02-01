/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 14:04:51 by fnieto            #+#    #+#             */
/*   Updated: 2016/02/01 23:14:18 by fnieto           ###   ########.fr       */
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

t_mat4		cam_perspective(t_float aspect, t_float fovy, t_float n, t_float f)
{
	t_float	v[2];
	t_mat4	new;

	new = mat4_identity();
	v[0] = tan(fovy * 0.5);
	v[1] = v[0] * aspect;
	new.m00 = 1 / v[1];
	new.m11 = 1 / v[0];
	new.m22 = -f - n / (f - n);
	new.m32 = -2 * f * n / (f - n);
	new.m23 = -1;
	new.m33 = 0;
	return (new);
}
