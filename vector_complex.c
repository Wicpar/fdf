/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_complex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 14:35:27 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/06 11:04:07 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_float	vec_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

t_vec	vec_cross(t_vec a, t_vec b)
{
	return (vec_new(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x, 0));
}

t_float	vec_lensq(t_vec a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
}

t_vec	vec_norm(t_vec a)
{
	t_float		len;

	len = SQRT(vec_lensq(a));
	a.x /= len;
	a.y /= len;
	a.z /= len;
	a.w /= len;
	return (a);
}
