/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 11:40:11 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/08 11:38:22 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>

static t_list	*file_to_lst(char *file)
{
	t_list		*lst;
	int			fd;
	char		*ln;
	
	fd = open(file, O_RDONLY);
	lst = 0;
	if (fd < 0)
		puterr(1, "File not Found or in use /!\\");
	while (get_next_line(fd, &ln) > 0)
		ft_lstadd(&lst, ft_lstnew(ln, ft_strlen(ln) + 1));
	close(fd);
	return (lst);
}

static void		bufferize(t_buffer *buf, t_list *lst)
{
	size_t	i;
	size_t	j;
	char	**temp;
	t_list	*tmp;

	tmp = lst;
	j = -1;
	while (tmp)
	{
		++j;
		i = -1;
		temp = ft_strsplit(tmp->content, ' ');
		while (temp[++i])
		{
			buff_set(buf, i, j, &temp[i]);
		}
		tmp = tmp->next;
	}
}

t_buffer		*file_to_strbuff(char *file)
{
	size_t		i[2];
	t_list		*lst[2];
	char		**ln;
	t_buffer	*buf;

	lst[0] = file_to_lst(file);
	lst[1] = lst[0];
	i[0] = 0;
	while ((lst[1]) != 0)
	{
		lst[1] = (lst[1])->next;
		i[0]++;
	}
	i[1] = 0;
	ln = ft_strsplit(lst[0]->content, ' ');
	while (ln[i[1]])
	{
		ft_memdel((void**)&ln[i[1]]);
		++i[1];
	}
	ft_memdel((void**)ln);
	buf = buff_new(i[1], i[0], sizeof(char*));
	bufferize(buf, lst[0]);
	return (buf);
}

t_buffer		*strbuff_to_vertbuff(t_buffer *buf)
{
	size_t		i[2];
	t_buffer	*new;
	t_vertex	tmp;
	char		**sep;

	new = buff_new(buf->w, buf->h, sizeof(t_vertex));
	ft_putendl("b");
	i[0] = -1;
	while (++i[0] < buf->h)
	{
		i[1] = -1;
		while (++i[1] < buf->w)
		{
			sep = ft_strsplit(*((char**)buff_get(buf, i[1], i[0])), ',');
			tmp.pos = vec_new(i[1] - (t_float)buf->w / 2,
					i[0] - (t_float)buf->w / 2, ft_atoi(sep[0]), 0);
			tmp.color = sep[1] ?
				ft_atoi_base(sep[1] + 2, "0123456789ABCDEF") : 0xFFFFFF;
			buff_set(new, i[1], i[0], &tmp);
			ft_memdel((void**)&sep);
		}
	}
	ft_putendl("b");
	buff_del(&buf);
	return (new);
}
