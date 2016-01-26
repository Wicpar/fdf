/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 11:40:11 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/26 18:26:42 by fnieto           ###   ########.fr       */
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

t_vec2		get_map_dim(t_list *map)
{
	t_vec2	new;
	t_list	*tmp;
	size_t	val;

	new = vec2(0, 0);
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

t_vertex	str_vert(t_vec2 pos, char *str)
{
	t_vertex	new;
	char		**buf;
	size_t		i;
	buf = ft_strsplit(str, ',');
	new.pos.x = pos.x;
	new.pos.y = pos.y;
	new.pos.z = ft_atoi(buf[0]);
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

t_buffer	*map_to_vert_buff(t_list *map)
{
	t_vec2		dim;
	t_list		*tmp[3];
	t_buffer	*new;
	dim = get_map_dim(map);
	new = buffer(dim.x, dim.y, sizeof(t_vertex));
	dim = vec2(0, 0);
	tmp[0] = map;
	while (tmp[0])
	{
		tmp[1] = *((t_list**)(tmp[0]->content));
		tmp[2] = tmp[1];
		dim.x = 0;
		while (tmp[1])
		{
			((t_vertex*)(new->buf))[(int)ROUND(new->w * dim.y + dim.x)] =
				str_vert(dim, (char*)(tmp[1]->content));
			dim.x++;
			tmp[1] = tmp[1]->next;
		}
		ft_lstdel(&(tmp[2]), &ft_lstfree_ptr);
		dim.y++;
		tmp[0] = tmp[0]->next;
	}
	ft_lstdel(&(map), &empty);
	return (new);
}
