/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 11:40:11 by fnieto            #+#    #+#             */
/*   Updated: 2016/02/03 17:56:37 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void		empty(void *ptr, size_t size)
{
	ptr = (void*)size;
}

t_list		*get_map_data(char *file)
{
	t_list	*new;
	t_list	*cur;
	char	*tmp;
	int		fd;
	new = 0;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &tmp) > 0)
	{
		cur = ft_str_split_lst(tmp, ' ');
		ft_lstpush(&new, ft_lstnew(&cur, sizeof(t_list*)));
		free(tmp);
	}
	close(fd);
	return (new);
}

t_vec4		get_map_dim(t_list *map)
{
	t_vec4	new;
	t_list	*tmp;
	size_t	val;

	new = vec4(0, 0, 0, 0);
	while (map)
	{
		new.y++;
		tmp = *((t_list**)(map->content));
		val = 0;
		while (tmp)
		{
			val++;
			tmp = tmp->next;
		}
		new.x = MAX(new.x, (t_float)val);
		map = map->next;
	}
	return (new);
}

t_vertex	str_vert(t_vec4 pos, char *str, t_map buffer, t_vec2 *h)
{
	t_vertex	new;
	char		**buf;
	size_t		i;

	buf = ft_strsplit(str, ',');
	new.pos.x = -(pos.x - buffer.buf->w / 2.);
	new.pos.y = pos.y - buffer.buf->h / 2.;
	new.pos.z = ft_atoi(buf[0]);
	h->x = MIN(h->x, new.pos.z);
	h->y = MAX(h->y, new.pos.z);
	free(buf[0]);
	i = -1;
	if (buf[1] && buf[1][0] == '0' && buf[1][1] == 'x')
	{

		new.attributes[0].value =
			(t_type)decode(ft_atoi_base(&(buf[1][2]), "0123456789ABCDEF"));
		new.attributes[0].interpolation = VEC4;
		free(buf[1]);
		++i;
	}
	free(buf);
	while (++i < 8)
		new.attributes[i] = attrib_null();
	return (new);
}

t_map		map_to_vert_buff(t_list *m)
{
	t_vec4		dim;
	t_list		*tmp[3];
	t_map		new;

	dim = get_map_dim(m);
	new = map(dim);
	dim = vec4(0, 0, 0, 0);
	tmp[0] = m;
	while (tmp[0])
	{
		tmp[1] = *((t_list**)(tmp[0]->content));
		tmp[2] = tmp[1];
		dim.x = 0;
		while (tmp[1])
		{
			set_vertex(new, dim.x, dim.y, str_vert(dim, (char*)(tmp[1]->content), new, &(new.height)));
			dim.x++;
			tmp[1] = tmp[1]->next;
		}
		ft_lstdel(&(tmp[2]), &ft_lstfree_ptr);
		dim.y++;
		tmp[0] = tmp[0]->next;
	}
	ft_lstdel(&(m), &empty);
	return (new);
}
