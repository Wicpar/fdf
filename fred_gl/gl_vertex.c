/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_vertex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 12:00:01 by fnieto            #+#    #+#             */
/*   Updated: 2016/02/04 20:51:41 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"
#include "libft.h"

static t_gl_vert_i	*i_cont(void)
{
	static t_gl_vert_i	i = {0, 0, {

	{0, {0}}, {0, {0}}, {0, {0}}, {0, {0}},
	{0, {0}}, {0, {0}}, {0, {0}}, {0, {0}}
	}, 0, 0};
	return (&i);
}

void				gl_begin(int draw_mode, t_shader s, t_frame *f)
{
	size_t		i;
	t_gl_vert_i	*info;

	if (s == 0 || f == 0 || draw_mode < 0)
		return ;
	info = i_cont();
	info->mode = draw_mode;
	info->shader = s;
	info->frame = f;
	i = -1;
	while (++i < 8)
	{
		info->attribs[i] = attrib_null();
	}
}

void				gl_param(t_type value, t_interp interpolation, int index)
{
	t_attrib	tmp;

	if (i_cont()->mode == -1)
		return ;
	tmp.interpolation = interpolation;
	tmp.value = value;
	i_cont()->attribs[index] = tmp;
}

void				gl_vertex(t_vec3 pos)
{
	t_vertex	new;
	size_t		i;
	t_gl_vert_i	*info;

	info = i_cont();
	if (info->mode == -1)
		return ;
	new = vertex(pos, info->attribs);
	ft_lstadd(&(info->lst), ft_lstnew(&new, sizeof(t_vertex)));
	i = -1;
	while (++i < 8)
	{
		info->attribs[i] = attrib_null();
	}
}

t_list				*gl_end(void)
{
	t_gl_vert_i					*info;
	t_list						*tmp;

	info = i_cont();
	if (info->mode == -1)
		return (0);
	tmp = info->lst;
	info->lst = 0;
	info->mode = -1;
	info->frame = 0;
	info->shader = 0;
	return (tmp);
}
