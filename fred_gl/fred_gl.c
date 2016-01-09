/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fred_gl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 19:45:30 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/09 11:00:20 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"

static t_instance		g_instance;

void		fred_gl_init(size_t w, size_t h, t_draw_func drawfn)
{
	g_instance.w = w;
	g_instance.h = h;
	g_instance.drawfn = drawfn;
	g_instance.enabled = 1;
}
