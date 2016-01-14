/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_vertex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 12:00:01 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/14 13:44:00 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"
#include "libft.h"

static t_list												*lst;
static int													mode;
static t_attrib												attribs[8];
static void (draw*)(t_list*, t_list*, t_shader, t_frame*)	funcs[] =
{&gl_lines}

void	gl_begin(int draw_mode)
{
	size_t	i;

	mode = draw_mode;
	i = -1;
	while (++i < 8)
	{
		attribs[i] = g_attrib_null;
	}
}

void	gl_param(t_type value, int interpolation, int index)
{
	t_attrib	tmp;

	index = CLAMP(index, 0, 7);
	tmp.interpolation = interpolation;
	tmp.value = value;
	attribs[index] = tmp;
}

void	gl_vertex(t_vec3 pos)
{
	t_vertex	new;
	size_t		i;

	new = vertex(pos, attribs);
	new = gl_transform(new);
	ft_lstpush(&lst, ft_lstnew(&new, sizeof(t_vertex)));
}


