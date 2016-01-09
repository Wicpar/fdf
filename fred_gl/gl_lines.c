/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_lines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 15:28:42 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/09 15:56:00 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"
#include "libft.h"

void		draw_line(t_vertex a, t_vertex b)
{
	int		max;

	max = MAX(b.pos.x - a.pos.x, b.pos.y - a.pos.y);
}
