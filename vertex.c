/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 09:02:16 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/07 09:39:25 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vertex		vert_lerp(t_vertex a, t_vertex b, t_float alpha)
{
	t_vertex new;

	new.pos = col_lerprgba(a.pos, b.pos, alpha);
	new.color = col_lerp(a.color, b.color, alpha);
	return (new);
}
