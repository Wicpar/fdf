/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 11:06:38 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/06 11:36:16 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat		mat_new(t_vec r1, t_vec r2, t_vec r3, t_vec r4)
{
	t_mat mat;

	mat.m00 = r1.x;
	mat.m10 = r1.y;
	mat.m20 = r1.z;
	mat.m30 = r1.w;
	mat.m01 = r2.x;
	mat.m11 = r2.y;
	mat.m21 = r2.z;
	mat.m31 = r2.w;
	mat.m02 = r3.x;
	mat.m12 = r3.y;
	mat.m22 = r3.z;
	mat.m32 = r3.w;
	mat.m03 = r4.x;
	mat.m13 = r4.y;
	mat.m23 = r4.z;
	mat.m33 = r4.w;
	return (mat);
}

t_mat		mat_identity(void)
{
	return (mat_new(
				vec_new(1, 0, 0, 0),
				vec_new(0, 1, 0, 0),
				vec_new(0, 0, 1, 0),
				vec_new(0, 0, 0, 1)));
}
