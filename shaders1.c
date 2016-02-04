/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 19:50:26 by fnieto            #+#    #+#             */
/*   Updated: 2016/02/04 23:49:14 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

t_vec3	hsv2rgb_smooth(t_vec3 c)
{
	t_vec3 rgb;

	rgb.x = CLAMP(fabs(fmod(c.x * 6.0, 6.0) - 3.0) - 1.0, 0.0, 1.0);
	rgb.y = CLAMP(fabs(fmod(c.x * 6.0 + 4.0, 6.0) - 3.0) - 1.0, 0.0, 1.0);
	rgb.z = CLAMP(fabs(fmod(c.x * 6.0 + 2.0, 6.0) - 3.0) - 1.0, 0.0, 1.0);
	rgb = mul_vec3(mul_vec3(rgb, rgb), sub_vec3(vec3_1(3), mul_vec3_1(rgb, 2)));
	return (mul_vec3_1(mix_vec3_1(vec3_1(1), rgb, c.y), c.z));
}

int		pass_shader(t_shader_info i)
{
	t_vec4 col;

	col = vec4(0.5, 0.5, 0.5, 0);
	if (i.i_vertex_attribs[1].interpolation == VEC4)
		col = i.i_vertex_attribs[1].value.v4;
	return (encode_vec4(col));
}

int		height(t_shader_info i)
{
	t_vec3 rgb;

	rgb = i.i_vertex_attribs[0].value.v3;
	rgb = hsv2rgb_smooth(vec3(rgb.z / 10. + i.i_global_time, 1, 1));
	return (encode_vec3(rgb));
}

int		sphere(t_shader_info i)
{
	t_vec3 rgb;

	rgb = i.i_vertex_attribs[0].value.v3;
	rgb = hsv2rgb_smooth(vec3(len_vec3(rgb) / 10. + i.i_global_time, 1, 1));
	return (encode_vec3(rgb));
}

int		palette_height(t_shader_info i)
{
	t_vec3 pos;

	pos = i.i_vertex_attribs[0].value.v3;
	if (pos.z < 0)
		return (encode(0, 0, 1. / (-pos.z / 8.)));
	pos.z /= i.i_vertex_attribs[2].value.v2.y;
	if (pos.z < 0.25)
		return (encode(1 - pos.z * 4, 1, 0));
	else if (pos.z < 0.5)
		return (encode_vec3(mix_vec3_1(vec3(0, 1, 0), vec3(0.45, 0.24, 0.1),
			(pos.z - 0.25) * 4)));
	else if (pos.z < 1)
		return (encode_vec3(mix_vec3_1(vec3(0.45, 0.24, 0.1),
			vec3_1(1), (pos.z - 0.5) * 2)));
	else
		return (0xFFFFFF);
}
