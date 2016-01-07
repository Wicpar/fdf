/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 08:22:36 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/04 16:25:16 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char			**split(char *str)
{
	size_t	n;
	size_t	i;
	size_t	len;
	char	**new;
	char	*tmp;

	len = ft_strlen(str);
	n = 0;
	tmp = str;
	while (*tmp)
	{
		if (*tmp == '\n')
		{
			*tmp = '\0';
			n++;
		}
		tmp++;
	}
	new = (char**)ft_memalloc((n + 2) * sizeof(char*));
	i = -1;
	tmp = str;
	while (++i <= n)
	{
		new[i] = ft_strdup(tmp);
		tmp = (char*)ft_memchr(tmp, 0, len - (str - tmp)) + 1;
	}
	return (new);
}

int				append_next_batch(t_fd *fd)
{
	char	buf[BUFF_SIZE + 1];
	int		n;
	char	*tmp;
	char	**newbuf;

	n = read(fd->fd, buf, BUFF_SIZE);
	buf[n] = 0;
	if (n > 0)
	{
		newbuf = split(buf);
		tmp = ft_strjoin(fd->buf[0], newbuf[0]);
		ft_memdel((void**)newbuf);
		*newbuf = tmp;
	}
	ft_memdel((void**)fd->buf);
	ft_memdel((void**)&fd->buf);
	if (n <= 0)
		return (n);
	fd->buf = newbuf;
	return (1);
}

t_fd			*get_current(t_list **fds, int const fd)
{
	t_list			*current;
	t_fd			new;
	t_fd			*tmp;

	current = *fds;
	while (current)
	{
		if (((t_fd*)current->content)->fd == fd)
			break ;
		current = current->next;
	}
	if (!current)
	{
		new.fd = fd;
		new.buf = split("");
		current = ft_lstnew(&new, sizeof(t_fd));
		ft_lstadd(fds, current);
	}
	tmp = (t_fd*)current->content;
	if (!tmp->buf)
		tmp->buf = split("");
	return (tmp);
}

int				get_next_line(int const fd, char **line)
{
	static t_list	*fds[1];
	t_fd			*tmp;
	int				status;

	tmp = get_current(fds, fd);
	while (tmp->buf[1] == 0 && (status = append_next_batch(tmp)) > 0)
		;
	if (status <= 0)
		return (status);
	*line = tmp->buf[0];
	status = 0;
	while (tmp->buf[status])
		++status;
	ft_memmove(tmp->buf, tmp->buf + 1, (status + 1) * sizeof(char*));
	return (1);
}
