/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_vertex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 12:00:01 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/14 19:30:24 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"
#include "libft.h"

static t_list												*lst;
static int													mode;
static t_attrib												attribs[8];
static void (*draw)(t_list*, t_shader, t_frame*)			funcs[] =
{&gl_lines}
static t_shader												shader;
static t_frame												*frame;

void	gl_begin(int draw_mode, t_shader s, t_frame *f)
{
	size_t	i;

	if (s == 0 || f == 0 || draw_mode < 0)
		return ;
	mode = CLAMP(draw_mode, 0, sizeof(funcs) / sizeof(*funcs) - 1);
	shader = s;
	frame = f;
	i = -1;
	while (++i < 8)
	{
		attribs[i] = g_attrib_null;
	}
}

void	gl_param(t_type value, t_interp interpolation, int index)
{
	t_attrib	tmp;

	if (mode == -1)
		return ;
	index = CLAMP(index, 0, 7);
	tmp.interpolation = interpolation;
	tmp.value = value;
	attribs[index] = tmp;
}

void	gl_vertex(t_vec3 pos)
{
	t_vertex	new;
	size_t		i;

	if (mode == -1)
		return ;
	new = vertex(pos, attribs);
	new = gl_transform(new);
	ft_lstpush(&lst, ft_lstnew(&new, sizeof(t_vertex)));
	i = -1;
	while (++i < 8)
	{
		attribs[i] = g_attrib_null;
	}
}

void	gl_end(void)
{
	if (mode == -1)
		return ;
	funcs[mode](lst, shader, frame);
	ft_lstdel(&lst, &ft_lstfree_ptr);
	mode = -1;
	frame = 0;
	shader = 0;
}

void	gl_draw_buf(t_list *buf, t_shader s, t_frame *f, int mode)
{
	mode = CLAMP(mode, 0, sizeof(funcs) / sizeof(*funcs) - 1);
	funcs[mode](buf, s, f);
}
