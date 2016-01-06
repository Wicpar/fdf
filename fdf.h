/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 12:31:54 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/06 11:54:35 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <string.h>

# define SQRT ft_sqrt_fast
# define SIN ft_sin_fast
# define PI 3.141592653589793238L

typedef	double		t_float;

typedef	union		u_sqrt_util
{
	float			f;
	unsigned long	ul;
}					t_sqrt_util;

typedef	struct		s_vec
{
	t_float	x;
	t_float	y;
	t_float	z;
	t_float	w;
}					t_vec;

typedef	struct		s_mat
{
	t_float	m00;
	t_float	m10;
	t_float	m20;
	t_float	m30;

	t_float	m01;
	t_float	m11;
	t_float	m21;
	t_float	m31;

	t_float	m02;
	t_float	m12;
	t_float	m22;
	t_float	m32;

	t_float	m03;
	t_float	m13;
	t_float	m23;
	t_float	m33;
}					t_mat;

t_vec				vec_new(t_float x, t_float y, t_float z, t_float w);
t_vec				vec_sub(t_vec a, t_vec b);
t_vec				vec_add(t_vec a, t_vec b);
t_vec				vec_mul(t_vec a, t_vec b);
t_vec				vec_div(t_vec a, t_vec b);

t_float				vec_dot(t_vec a, t_vec b);
t_vec				vec_cross(t_vec a, t_vec b);
t_float				vec_lensq(t_vec a);
t_vec				vec_norm(t_vec a);

t_float				ft_sqrt_fast(t_float x);

t_mat				mat_new(t_vec r1, t_vec r2, t_vec r3, t_vec r4);
t_mat				mat_identity(void);

#endif
