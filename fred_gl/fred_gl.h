/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fred_gl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 14:05:50 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/08 20:11:32 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRED_GL_H
# define FRED_GL_H

# include <string.h>

# define ABS(a) (a < 0 ? -a : a)
# define MIN(a, b) (a < b ? a : b)
# define MAX(a, b) (a > b ? a : b)
# define FLOOR(a) ((long)a)
# define CEIL(a) (FRACT(a) != 0. ? FLOOR(a + 1) : FLOOR(a))
# define FRACT(a) (a - FLOOR(a))
# define MOD(a, b) (FRACT(a / b) * b)
# define SIGN(a) (a < 0 ? -1 : 1)
# define CLAMP(a, min, max) (MIN(MAX(a, min), max))
# define MIX(a, b, alpha) (a * (1 - alpha) + b * alpha)
# define SMSTUTIL(x) (x * x * (3.0 - 2.0 * x))
# define SMOOTHSTEP(e0, e1, x) (SMSTUTIL(clamp((x - e0) / (e1 - e0), 0.0, 1.0));
# define STEP(edge, x) (x >= edge)
# define ATAN(x, y) (PI - atan(y/x) + (x < 0. ? -PI * 2 : PI ))
# define LERP(a, b, x, max) (x * (max / (b - a)))
# define ROUND(a) (FRACT(a) > 0.5 ? CEIL(a) : FLOOR(a))

# define GL_ALL 0
# define GL_LEQUAL -1
# define GL_GEQUAL 1

typedef	double		t_float;

typedef	union		u_converter
{
	short			s;
	unsigned short	us;
	int				i;
	unsigned int	ui;
	long			l;
	unsigned long	ul;
	float			f;
	double			d;
	char			c;
	unsigned char	uc;
}					t_converter;

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

typedef	struct		s_shader_info
{
	t_vec2		i_frag_coord;
	t_vec3		i_world_pos;
	t_vec2		i_resolution;
	t_float		i_global_time;
	t_float		i_time_delta;
}					t_shader_info;

typedef	struct		s_buffer
{
	size_t	w;
	size_t	h;
	size_t	type;
	void	*buf;
}					t_buffer;

typedef	int	(*t_shader)(t_shader_info shader_info);
typedef	int	(*t_draw_func)(int x, int y, int color);

typedef	struct		s_frame
{
	int				clear_undrawn;
	int				depth_func;
	t_buffer		*img;
	t_buffer		*depth;
}					t_frame;

typedef	struct		s_instance
{
	size_t	w;
	size_t	h;
	t_frame	*frame;
}					t_instance;

extern t_draw_func	g_draw;

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

int					encode(t_float r, t_float g, t_float b);
int					encode_vec3(t_vec3 color);
int					encode_vec4(t_vec4 color);

t_vec3				decode(int color);

int					f_to_i(float f);
float				i_to_f(int i);

#endif
