/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fred_gl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 14:05:50 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/08 15:11:45 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRED_GL_H
# define FRED_GL_H

# define ABS(a) (a < 0 ? -a : a)
# define MIN(a, b) (a < b ? a : b)
# define MAX(a, b) (a > b ? a : b)
# define FRACT(a) (a - (long)a)
# define MOD(a, b) (FRACT(a / b) * b)
# define SIGN(a) (a < 0 ? -1 : 1)
# define CLAMP(a, min, max) (MIN(MAX(a, min), max))
# define MIX(a, b, alpha) (a * (1 - alpha) + b * alpha)
# define SMSTUTIL(x) (x * x * (3.0 - 2.0 * x))
# define SMOOTHSTEP(edge0, edge1, x) (SMSTUTIL(clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0));

typedef	double		t_float;

typedef	struct		s_vec2
{
	t_float	x;
	t_float	y;
}					t_vec2;

typedef	struct		s_vec3
{
	t_float	x;
	t_float	y;
	t_float	z;
}					t_vec3;

typedef	struct		s_vec4
{
	t_float	x;
	t_float	y;
	t_float	z;
	t_float	w;
}					t_vec4;

t_vec2				vec2(t_float x, t_float y);
t_vec2				vec2_1(t_float x);

t_vec2				add_vec2(t_vec2 a, t_vec2 b);
t_vec2				sub_vec2(t_vec2 a, t_vec2 b);
t_vec2				mul_vec2(t_vec2 a, t_vec2 b);
t_vec2				div_vec2(t_vec2 a, t_vec2 b);

t_vec2				add_vec2_1(t_vec2 a, t_float b);
t_vec2				sub_vec2_1(t_vec2 a, t_float b);
t_vec2				mul_vec2_1(t_vec2 a, t_float b);
t_vec2				div_vec2_1(t_vec2 a, t_float b);

t_vec3				vec3(t_float x, t_float y, t_float z);
t_vec3				vec3_1(t_float x);

t_vec3				add_vec3(t_vec3 a, t_vec3 b);
t_vec3				sub_vec3(t_vec3 a, t_vec3 b);
t_vec3				mul_vec3(t_vec3 a, t_vec3 b);
t_vec3				div_vec3(t_vec3 a, t_vec3 b);

t_vec3				add_vec3_1(t_vec3 a, t_float b);
t_vec3				sub_vec3_1(t_vec3 a, t_float b);
t_vec3				mul_vec3_1(t_vec3 a, t_float b);
t_vec3				div_vec3_1(t_vec3 a, t_float b);

t_vec4				vec4(t_float x, t_float y, t_float z, t_float w);
t_vec4				vec4_1(t_float x);

t_vec4				add_vec4(t_vec4 a, t_vec4 b);
t_vec4				sub_vec4(t_vec4 a, t_vec4 b);
t_vec4				mul_vec4(t_vec4 a, t_vec4 b);
t_vec4				div_vec4(t_vec4 a, t_vec4 b);

t_vec4				add_vec4_1(t_vec4 a, t_float b);
t_vec4				sub_vec4_1(t_vec4 a, t_float b);
t_vec4				mul_vec4_1(t_vec4 a, t_float b);
t_vec4				div_vec4_1(t_vec4 a, t_float b);

#endif
