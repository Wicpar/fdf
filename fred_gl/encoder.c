/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 18:50:28 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/08 19:16:23 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"

int			encode_vec4(t_vec4 color)
{
	t_converter		val;

	val.ui = 0;
	val.ui += ROUND(CLAMP(color.w, 0., 1.) * 255);
	val.ui <<= 8;
	val.ui += ROUND(CLAMP(color.x, 0., 1.) * 255);
	val.ui <<= 8;
	val.ui += ROUND(CLAMP(color.y, 0., 1.) * 255);
	val.ui <<= 8;
	val.ui += ROUND(CLAMP(color.z, 0., 1.) * 255);
	return (val.i);
}

int			encode_vec3(t_vec3 color)
{
	t_converter		val;

	val.ui = 0;
	val.ui += ROUND(CLAMP(color.x, 0., 1.) * 255);
	val.ui <<= 8;
	val.ui += ROUND(CLAMP(color.y, 0., 1.) * 255);
	val.ui <<= 8;
	val.ui += ROUND(CLAMP(color.z, 0., 1.) * 255);
	return (val.i);
}

int			encode(t_float r, t_float g, t_float b)
{
	t_converter		val;

	val.ui = 0;
	val.ui += ROUND(CLAMP(r, 0., 1.) * 255);
	val.ui <<= 8;
	val.ui += ROUND(CLAMP(g, 0., 1.) * 255);
	val.ui <<= 8;
	val.ui += ROUND(CLAMP(b, 0., 1.) * 255);
	return (val.i);
}
