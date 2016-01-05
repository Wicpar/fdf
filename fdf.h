/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 12:31:54 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/05 13:29:27 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <string.h>

typedef	double		t_float;

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

#endif
