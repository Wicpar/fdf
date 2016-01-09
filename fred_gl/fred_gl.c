/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fred_gl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 19:45:30 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/09 19:59:00 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"
#include "libft.h"

t_instance		*g_instance;
t_float			g_global_time = 0.;

void		fred_gl_init(size_t w, size_t h, t_draw_func drawfn)
{
	g_instance = (t_instance*)ft_memalloc(sizeof(t_instance));
	if (!g_instance)
		return ;
	g_instance->w = w;
	g_instance->h = h;
	g_instance->drawfn = drawfn;
	g_instance->frame = frame(w, h);
	g_global_time = 0.;
}

void		fred_gl_deinit(void)
{
	frame_del(&(g_instance->frame));
	ft_memdel((void**)&g_instance);
}
