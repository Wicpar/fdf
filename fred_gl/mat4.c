/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 12:02:27 by fnieto            #+#    #+#             */
/*   Updated: 2016/02/01 23:46:48 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"
#include <math.h>

t_mat4		mat4(t_vec4 r1, t_vec4 r2, t_vec4 r3, t_vec4 r4)
{
	t_mat4	new;

	new.m00 = r1.x;
	new.m10 = r1.y;
	new.m20 = r1.z;
	new.m30 = r1.w;
	new.m01 = r2.x;
	new.m11 = r2.y;
	new.m21 = r2.z;
	new.m31 = r2.w;
	new.m02 = r3.x;
	new.m12 = r3.y;
	new.m22 = r3.z;
	new.m32 = r3.w;
	new.m03 = r4.x;
	new.m13 = r4.y;
	new.m23 = r4.z;
	new.m33 = r4.w;
	return (new);
}

t_mat4		mat4_identity(void)
{
	static const t_mat4	identity = {
		1., 0., 0., 0.,
		0., 1., 0., 0.,
		0., 0., 1., 0.,
		0., 0., 0., 1.};

	return (identity);
}

t_mat4		mat4_scale(t_vec3 scale)
{
	t_mat4	new;

	new = mat4_identity();
	new.m00 = scale.x;
	new.m11 = scale.y;
	new.m22 = scale.z;
	return (new);
}

t_mat4		mat4_translation(t_vec3 translation)
{
	t_mat4	new;

	new = mat4_identity();
	new.m30 = translation.x;
	new.m31 = translation.y;
	new.m32 = translation.z;
	return (new);
}

t_mat4		mat4_rotation(t_float rotx, t_float roty, t_float rotz)
{
	t_mat4	new;
	t_float	v[6];

	new = mat4_identity();
	v[0] = cos(rotx);
	v[1] = sin(rotx);
	v[2] = cos(roty);
	v[3] = sin(roty);
	v[4] = cos(rotz);
	v[5] = sin(rotz);
	new.m20 = v[3];
	new.m21 = -v[1] * v[2];
	new.m22 = v[0] * v[2];
	new.m00 = v[2] * v[4];
	new.m01 = v[1] * v[3] * v[4] + v[0] * v[5];
	new.m02 = -v[3] * v[0] * v[4] + v[1] * v[5];
	new.m10 = -v[5] * v[2];
	new.m11 = -v[5] * v[1] * v[3] + v[0] * v[4];
	new.m12 = v[5] * v[3] * v[0] + v[1] * v[4];
	return (new);
}
