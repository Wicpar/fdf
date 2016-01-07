/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matvec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 08:16:52 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/07 08:24:44 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec		matvec_mul(t_mat mat, t_vec vec)
{
	t_vec	new;

	new.x = mat.m00 * vec.x +
			mat.m10 * vec.y +
			mat.m20 * vec.z +
			mat.m30 * vec.w;
	new.y = mat.m01 * vec.x +
			mat.m11 * vec.y +
			mat.m21 * vec.z +
			mat.m31 * vec.w;
	new.z = mat.m02 * vec.x +
			mat.m12 * vec.y +
			mat.m22 * vec.z +
			mat.m32 * vec.w;
	new.w = mat.m03 * vec.x +
			mat.m13 * vec.y +
			mat.m23 * vec.z +
			mat.m33 * vec.w;
	return (new);
}
