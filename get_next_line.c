/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 08:22:36 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/13 21:00:30 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

t_list			*split(char *str)
{
	t_list		*new;
	char		*tmp1;
	char		*tmp2;

	new = 0;
	tmp1 = str;
	while ((tmp2 = ft_strchr(tmp1, '\n')))
	{
		*tmp2 = 0;
		ft_lstpush(&new, ft_lstnew(tmp1, tmp2 - tmp1 + 1));
		tmp1 = tmp2 + 1;
	}
	ft_lstpush(&new, ft_lstnew(tmp1, ft_strlen(tmp1) + 1));
	return (new);
}

int				append_next_batch(t_fd *fd)
{
	char	buf[BUFF_SIZE + 1];
	int		n;
	char	*swap;
	t_list	*tmp;
	t_list	*newbuf;

	n = read(fd->fd, buf, BUFF_SIZE);
	if (n > 0)
	{
		buf[n] = 0;
		buf[BUFF_SIZE] = 0;
		newbuf = split(buf);
		tmp = ft_lstpop(&(fd->buf));
		swap = tmp->content;
		tmp->content = ft_strjoin(swap, newbuf->content);
		tmp->content_size = ft_strlen(tmp->content) + 1;
		free(newbuf->content);
		free(swap);
		free(ft_lstremove(&newbuf));
		tmp->next = newbuf;
		ft_lstpush(&(fd->buf), tmp);
		return (1);
	}
	return (n);
}

t_fd			*get_current(t_list **fds, int const fd)
{
	t_list			**cur;
	t_list			*tmp;
	t_fd			*ret;

	cur = fds;
	while (cur && *cur)
	{
		if (((t_fd*)((*cur)->content))->fd == fd)
			break ;
		cur = (*cur)->next ? &((*cur)->next) : 0;
	}
	if (cur && *cur)
	{
		tmp = *cur;
		*cur = (*cur)->next;
		ret = (t_fd*)(tmp->content);
		free(tmp);
		return (ret);
	}
	ret = (t_fd*)ft_memalloc(sizeof(t_fd));
	ret->fd = fd;
	ret->buf = ft_lstnew("", 1);
	return (ret);
}

char			*extract(t_fd *fd)
{
	char	*line;
	t_list	*tmp;

	line = 0;
	if (fd->buf)
	{
		line = fd->buf->content;
		tmp = fd->buf;
		fd->buf = fd->buf->next;
		free(tmp);
	}
	return (line);
}

int				get_next_line(int const fd, char **line)
{
	static t_list	*fds[1];
	t_fd			*tmp;
	int				status;
	size_t			count;

	if (fd <= -1 || !line || BUFF_SIZE < 1)
		return (-1);
	status = 1;
	count = 0;
	tmp = get_current(fds, fd);
	while (!(tmp->buf->next) && (status = append_next_batch(tmp)) > 0)
		++count;
	*line = extract(tmp);
	if (status < 0 || !(count || status || **line))
		ft_memdel((void**)line);
	if (status > -1 && tmp->buf)
		ft_lstadd(fds, ft_lstnew(tmp, sizeof(t_fd)));
	free(tmp);
	return (status ? status : (*line != 0));
}
