/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 08:39:02 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/08 12:34:45 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec		col_torgba(int color)
{
	t_vec	new;
	new.x = (t_float)((color & 0x00FF0000) >> 16) / 255.;
	new.y = (t_float)((color & 0x0000FF00) >> 8) / 255.;
	new.z = (t_float)((color & 0x000000FF) >> 0) / 255.;
	new.w = (t_float)((color & 0xFF000000) >> 24) / 255.;
	return (new);
}

int			col_fromrgba(t_vec rgba)
{
	int	i;

	i = 0;
	i += (((int)(CLAMP(rgba.x, 0, 1) * 255)) << 16);
	i += (((int)(CLAMP(rgba.y, 0, 1) * 255)) << 8);
	i += (((int)(CLAMP(rgba.z, 0, 1) * 255)) << 0);
	i += (((int)(CLAMP(rgba.w, 0, 1) * 255)) << 24);
	return (i);
}

t_vec		col_lerprgba(t_vec cola, t_vec colb, t_float alpha)
{
	t_vec res;

	res.x = LERP(cola.x, colb.x, alpha);
	res.y = LERP(cola.y, colb.y, alpha);
	res.z = LERP(cola.z, colb.z, alpha);
	res.w = LERP(cola.w, colb.w, alpha);
	return (res);
}

int			col_lerp(int cola, int colb, t_float alpha)
{
	int col;

	col = col_fromrgba(col_lerprgba(col_torgba(cola), col_torgba(colb), alpha));
	return (col);
}
