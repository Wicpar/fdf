/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 21:46:43 by fnieto            #+#    #+#             */
/*   Updated: 2016/02/04 22:55:54 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

t_type		*var(int i)
{
	static t_type vars[100];

	return (&(vars[i]));
}

void		init_controls(t_vec2 map)
{
	SV(C_TRANS, vec3(0, 0, 100));
	SV(C_ANGLS, vec3(0, -PI, -PI));
	SV(C_HEIGHT, ((t_float)(0.5)));
	SV(C_ZOOM, ((t_float)(asin((MAX(map.x, map.y) + 2) / 100) / (PI / 2))));
}