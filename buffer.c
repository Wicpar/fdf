/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 11:13:00 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/07 11:40:07 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

t_buffer	*buff_new(size_t w, size_t h, size_t typesize)
{
	t_buffer	*new;
	void		*buffer;

	buffer = (void*)ft_memalloc(w * h * typesize);
	if (!buffer)
		return (0);
	new = (t_buffer*)ft_memalloc(sizeof(t_buffer));
	if (!new)
		return (0);
	new->w = w;
	new->h = h;
	new->buf = buffer;
	new->typesize = typesize;
	return (new);
}

void	*buff_get(t_buffer *buf, size_t x, size_t y)
{
	return (buf->buf + y * buf->w + x);
}

void	buff_set(t_buffer *buf, size_t x, size_t y, void *val)
{
	ft_memmove(buff_get(buf, x, y), val, buf->typesize);
}

void	buff_del(t_buffer **buf)
{
	ft_memdel((void*)&((*buf)->buf));
	ft_memdel((void*)buf);
}
